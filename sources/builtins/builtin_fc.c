/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 13:54:45 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 01:45:33 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

static int		builtin_fc_init_op(char **args, char **op)
{
	int i;

	i = 0;
	if ((args[0] && (i = builtin_get_options(op, args, "elnrs")) == -1) ||
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

t_shell		*builtin_fc_init_cmd(t_shell *shell)
{
	t_shell *shl;

	if (!(shl = malloc(sizeof(t_shell))))
		exit(EXIT_FAILURE);
	ft_bzero(shl, sizeof(t_shell));
	shl->envp = shell->envp;
	shl->envl = shell->envl;
	shl->alias = shell->alias;
	shl->t = shell->t;
	shl->hist = shell->hist;
	return (shl);
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

int		builtin_fc_search_occurence(t_fc *fc, t_data *hist)
{
	t_data *tmp;
	int	first_occurence;
	int first_nb;
	int last_nb;

	first_occurence = 0;
	tmp = hist;
	if (!(last_nb = 0) && ((first_nb = builtin_search_occurence_pos(fc,
	hist, 0)) != -1) && fc->last)
		last_nb = builtin_search_occurence_pos(fc, hist, 1);
	if (first_nb == -1 || last_nb == -1 || (ft_strlen(fc->op) == 1
	&& (ft_strchr(fc->op, 'e') && (fc->fd = open("/tmp/.fc_cmd_list", O_WRONLY | O_CREAT |
	O_APPEND | O_TRUNC, 0644) < 0))))
		return (1);
	printf("bef_nb: %d\n", tmp->nb);
	printf("len_int: %d\n", ft_lenint(tmp->nb));
	while (tmp)
	{
		if ((!first_occurence && first_nb == tmp->nb && (first_occurence = 1))
		|| (first_occurence && last_nb && first_nb != tmp->nb))
		{
			if (fc->op && ft_strchr(fc->op, 'l') && !ft_strchr(fc->op, 'n'))
				dprintf(2, "nb: %d\t", tmp->nb);
			dprintf(2, "cmd: %s\n", tmp->cmd);
		}
		if (first_occurence && (!last_nb || first_nb == last_nb || last_nb == tmp->nb))
			break ;
		tmp = first_occurence && last_nb > first_nb ? tmp->next : tmp->prev;
	}
	return (0);
}

void	builtin_fc_search_first_and_last(char **args, t_fc *fc)
{
	int nb;

	nb = 0;
	if (ft_strlen(fc->op) == 1 && fc->op[0] == 'e')
		fc->editor = args[++fc->i];
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

int		builtin_fc(char **args, t_shell *shell)
{
	t_fc	*fc;

	(void)shell;
	if (!(fc = malloc(sizeof(t_fc))))
		exit(EXIT_FAILURE);
	ft_bzero(fc, sizeof(t_fc));
	fc->i = -1;
	if (args[0] && args[0][0] == '-' && !ft_isdigit(args[0][1])
	&& (fc->i = builtin_fc_init_op(args, &fc->op) - 1) == -2)
		return (1);
	//fc->shl = builtin_fc_init_cmd(shell);
	builtin_fc_search_first_and_last(args, fc);
	dprintf(2, "editor: %s\n", fc->editor);
	if (fc->first && builtin_fc_search_occurence(fc, shell->hist))
		return (1);
//	dprintf(2, "ops: %s\n", fc->op);
//	dprintf(2, "first: %s\n", fc->first);
//	dprintf(2, "last: %s\n", fc->last);
	//ret = shell();
	return (0);
}
