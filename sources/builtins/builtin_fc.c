/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 13:54:45 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 10:39:29 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

static int		builtin_fc_init_op(char **args, char **op)
{
	int i;

	i = 0;
	if ((args[0] && (i = builtin_get_options(op, args, "elnrs", 1)) == -1) ||
	(*op && ft_strchr(*op, 'e') && !args[i]))
	{
		i == -1 ? ft_dprintf(2, "42sh: fc: -%s: invalid option\n", *op)
		: ft_putstr_fd("42sh: fc: -e: option requires an argument\n", 2);
		ft_putstr_fd("fc: usage: fc [-e ename] [-lnr] [first] [last] or"
		" fc -s [pat=rep] [command]\n", 2);
		ft_strdel(op);
		return (-1);
	}
	return (i);
}

int			builtin_fc_correct_ret(ret)
{
	if (ret == 131)
		ret = 3;
	else if (ret == 146)
		ret = 4735;
	else
		ret *= 256;
	return (ret);
}

static int		builtin_fc_exit(t_fc **fc)
{
	int		ret;
	t_data	*tmp;

	ret = (*fc)->ret;
	ft_strdel(&(*fc)->first);
	ft_strdel(&(*fc)->last);
	ft_strdel(&(*fc)->op);
	while ((*fc)->cmd_list)
	{
		tmp = (*fc)->cmd_list->next;
		ft_strdel(&(*fc)->cmd_list->cmd);
		free((*fc)->cmd_list);
		(*fc)->cmd_list = tmp;
	}
	free((*fc));
	unlink("/tmp/.42sh-fc_cmd_list");
	ret = builtin_fc_correct_ret(ret);
	return (ret);
}

static int		builtin_fc_init(t_fc **fc, t_shell *shell, char **args)
{
	if (!(*fc = ft_memalloc(sizeof(t_fc))))
		exit(EXIT_FAILURE);
	(*fc)->i = -1;
	(*fc)->fd = -1;
	if (args[0] && args[0][0] == '-'
	&& ((*fc)->i = builtin_fc_init_op(args, &(*fc)->op) - 1) == -2)
		return (((*fc)->ret = 1));
	if (!(*fc)->op && !((*fc)->editor =
	ft_strdup(get_envp(shell->envp, "FCEDIT"))))
		(*fc)->editor = ft_strdup("vi");
	else if ((*fc)->op && ft_strchr((*fc)->op, 'e')
	&& !ft_strchr((*fc)->op, 'l') && !ft_strchr((*fc)->op, 's'))
		(*fc)->editor = ft_strdup(args[++(*fc)->i]);
	if ((*fc)->editor)
	{
		ft_strjoin_free(&(*fc)->editor, " /tmp/.42sh-fc_cmd_list");
		ft_strdel(&shell->str);
		shell->str = (*fc)->editor;
	}
	return (0);
}

void			builtin_fc_set_state_fc(void)
{
	t_job	*job;
	t_cmd	*elem;

	job = getter_job()->first_job;
	while ((job = job->next))
	{
		if (job->state != -1)
		{
			elem = job->cmds;
			while (elem)
			{
				if (!ft_strcmp(elem->args[0], "fc"))
				{
					job->state = -1;
					return ;
				}
				elem = elem->next_cmd;
			}
		}
	}
}

int				builtin_fc(char **args, t_shell *shell)
{
	t_fc	*fc;

	builtin_fc_set_state_fc();
	if (!builtin_fc_init(&fc, shell, args))
	{
		builtin_fc_search_first_and_last(args, fc);
		if (!fc->first || (fc->first &&
		!(fc->ret = builtin_fc_search_occurence(fc, shell->hist))))
			if (!fc->op || ((ft_strchr(fc->op, 'e') || ft_strchr(fc->op, 's'))
			&& !ft_strchr(fc->op, 'l')))
			{
				builtin_fc_execute_commands(fc, shell);
			}
	}
	return (builtin_fc_exit(&fc));
}
