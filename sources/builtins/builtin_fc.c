/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 13:54:45 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/01 13:04:11 by dewalter    ###    #+. /#+    ###.fr     */
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

int		builtin_search_occurence_pos(t_fc *fc, t_data *hist, int pos)
{
	t_data *tmp;
	int cmd_nb;
	int nb;
	char *occurence;

	tmp = hist->prev->prev;
	occurence = !pos ? fc->first : fc->last;
	cmd_nb = -1;
	nb = ft_atoi(occurence);
	if (tmp && ft_isdigit(occurence[occurence[0] == '-' ? 1 : 0]))
	{
		if (nb < 0 && ((nb + 1) + tmp->nb) > 0)
			cmd_nb = (nb + 1) + tmp->nb;
		else if (nb > 0 && nb <= tmp->nb)
			cmd_nb = nb;
	}
	while (!nb && tmp && ((tmp->cmd &&
	ft_strncmp(tmp->cmd, occurence, ft_strlen(occurence))) || !tmp->cmd))
		tmp = tmp->prev;
	if (!nb && tmp)
		cmd_nb = tmp->nb;
	if (cmd_nb == -1)
		ft_putstr_fd("42sh: fc: history specification out of range\n", 2);
	return (cmd_nb);
}

void	builtin_fc_browse_history_for_occurence(t_fc *fc, int first_nb,
		int last_nb, t_data *hist)
{
	t_data *tmp;
	int	first_occurence;

	tmp = hist;
	first_occurence = 0;
	while (tmp && !(first_occurence && (!last_nb || first_nb == last_nb ||
		((last_nb < 0 ? last_nb - 1 : last_nb + 1)) == tmp->nb)))
	{
		if ((!first_occurence && first_nb == tmp->nb && (first_occurence = 1))
		|| (first_occurence && last_nb && first_nb != tmp->nb))
		{
			if (fc->fd >= 0)
			{
				ft_putstr_fd(tmp->cmd, fc->fd);
				ft_putstr_fd("\n", fc->fd);
			}
			else
			{
				if (fc->op && ft_strchr(fc->op, 'l') && !ft_strchr(fc->op, 'n'))
					dprintf(2, "%d\t", tmp->nb);
				dprintf(2, "%s\n", tmp->cmd);
			}
		}
		tmp = first_occurence && last_nb > first_nb ? tmp->next : tmp->prev;
	}
}

void	ft_swap(int *a, int *b)
{
	int c;

	c = *a;
	*a = *b;
	*b = c;
}

int		builtin_fc_search_occurence(t_fc *fc, t_data *hist)
{
	int first_nb;
	int last_nb;

	first_nb = 0;
	last_nb = 0;
	if (((first_nb = builtin_search_occurence_pos(fc,
	hist, 0)) != -1) && fc->last)
		last_nb = builtin_search_occurence_pos(fc, hist, 1);
	if (first_nb == -1 || last_nb == -1 || ((!fc->op || (fc->op
	&& ft_strchr(fc->op, 'e') && !ft_strchr(fc->op, 'l'))) &&
	((fc->fd = open("/tmp/.42sh-fc_cmd_list",
	O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644)) < 0)))
		return (1);
	if (first_nb && last_nb && fc->op && ft_strchr(fc->op, 'r'))
		ft_swap(&first_nb, &last_nb);
	builtin_fc_browse_history_for_occurence(fc, first_nb, last_nb, hist);
	if (fc->fd >= 0)
		close(fc->fd);
	return (0);
}

void	builtin_fc_search_first_and_last(char **args, t_fc *fc)
{
	int nb;

	nb = 0;
	while(args && args[++fc->i] && nb < 2)
	{
		if ((args[fc->i][0] == '-' && ft_isdigit(args[fc->i][1])) ||
				ft_isdigit(args[fc->i][0]))
			!nb ? (fc->first = ft_itoa(ft_atoi(args[fc->i])))
				: (fc->last = ft_itoa(ft_atoi(args[fc->i])));
		else
			!nb ? (fc->first = ft_strdup(args[fc->i]))
				: (fc->last = ft_strdup(args[fc->i]));
		nb++;
	}
	if (!fc->first && fc->op && ft_strchr(fc->op, 'l'))
	{
		fc->first = ft_strdup("-15");
		fc->last = ft_strdup("-1");
	}
	else if (!fc->first)
		fc->first = ft_strdup("-1");
}

int		builtin_fc_exit(t_fc **fc)
{
	int ret;

	ret = (*fc)->ret;
	ft_strdel(&(*fc)->first);
	ft_strdel(&(*fc)->last);
	ft_strdel(&(*fc)->op);
	free((*fc));
	return (ret);
}

void	builtin_fc_remove_hist_node(t_shell *shell)
{
	t_data *tmp;
	t_data *tmp1;

	tmp = shell->hist->prev;
	shell->hist = shell->hist->prev->prev;
	ft_strdel(&shell->hist->cmd);
	shell->hist->next = NULL;
	while (tmp)
	{
		if (tmp->cmd)
			ft_strdel(&tmp->cmd);
		tmp1 = tmp->next;
		free(tmp);
		tmp = tmp1;
	}
}

void	builtin_fc_execute_commands(t_fc *fc, t_shell *shell)
{
	t_data *cmd_list;
	t_data *tmp;
	t_prompt prompt;

	prompt = PROMPT;
	if (!fc->op || (!ft_strchr(fc->op, 's') && ft_strchr(fc->op, 'e')))
		if ((fc->ret = shell_command_execution(shell, NULL, 0, &prompt) == -1)
		 || ((ft_atoi(get_envp(shell->envl, "?"))) == 1))
			return ;
	builtin_fc_remove_hist_node(shell);
	cmd_list = init_hist("/tmp/.42sh-fc_cmd_list");
	while (cmd_list->prev)
		cmd_list = cmd_list->prev;
	while (cmd_list)
	{
		if ((shell->str = cmd_list->cmd) && write(1, cmd_list->cmd,
		ft_strlen(cmd_list->cmd)) && write(1, "\n", 1))
			if ((fc->ret = shell_command_execution(shell, NULL, 0,
			&prompt)) == -1)
				return ;
		dprintf(2, "fc->ret: %d\n", fc->ret);
		tmp = cmd_list->next;
		free(cmd_list);
		cmd_list = tmp;
	}
}

int		builtin_fc_init(t_fc **fc, t_shell *shell, char **args)
{
	if (!(*fc = ft_memalloc(sizeof(t_fc))))
		exit(EXIT_FAILURE);
	(*fc)->i = -1;
	(*fc)->fd = -1;
	if (args[0] && args[0][0] == '-'
	&& ((*fc)->i = builtin_fc_init_op(args, &(*fc)->op) - 1) == -2)
		return (1);
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

int		builtin_fc(char **args, t_shell *shell)
{
	t_fc	*fc;
	int		ret;

	if (!(ret = builtin_fc_init(&fc, shell, args)))
	{
		builtin_fc_search_first_and_last(args, fc);
		if (!fc->first || (fc->first && !(ret = builtin_fc_search_occurence(fc, shell->hist))))
			if (!fc->op || (ft_strchr(fc->op, 'e') && !ft_strchr(fc->op, 'l')))
				builtin_fc_execute_commands(fc, shell);
	}
	dprintf(2, "ret: %d\n", fc->ret);
	return (builtin_fc_exit(&fc));
}
