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

	nb = 1;
	dprintf(2, "cmd: %s\n", hist->cmd);
	dprintf(2, "cmd+1: %s\n", hist->prev->cmd);
	tmp = !hist->cmd ? hist->prev->prev : hist->prev;
	cmd_nb = -1;
	occurence = !pos ? fc->first : fc->last;
	dprintf(2, "nb: %d\n", ft_atoi(occurence));
	while (tmp)
	{
		dprintf(2, "res: %d\n", ft_atoi(occurence) + nb);
		dprintf(2, "cmd: %s\n", tmp->cmd);

		//if ()
		if (tmp->cmd && ((ft_isdigit(occurence[occurence[0] == '-' ? 1 : 0])
		&& ((ft_atoi(occurence) >= 0 && ft_atoi(occurence) == tmp->nb)
		|| (ft_atoi(occurence) < 0 && !(ft_atoi(occurence) + nb))))))
		{
			dprintf(2, "tmp->nb: %d\n", tmp->nb);
			cmd_nb = tmp->nb;
			break ;
		}
		nb++;
		tmp = tmp->prev;
	}
	return (cmd_nb);
}

int		builtin_fc_search_first_occurence(t_fc *fc, t_data *hist)
{
	t_data *tmp;
	int first_nb;
	int last_nb;

	tmp = hist;

	first_nb = builtin_search_occurence_pos(fc, hist, 0);
	last_nb = !fc->last ? 0 : builtin_search_occurence_pos(fc, hist, 1);

	dprintf(2, "first_nb: %d\n", first_nb);
	dprintf(2, "last_nb: %d\n", last_nb);
	if (first_nb == -1 || last_nb == -1)
	{
		ft_putstr_fd("42sh: fc: history specification out of range\n", 2);
		return (1);
	}
	while (tmp)
	{
		if (!(fc->lst_cmd) && first_nb == tmp->nb)
		{
			if (!(fc->lst_cmd = malloc(sizeof(t_data))))
				exit(EXIT_FAILURE);
			ft_bzero(fc->lst_cmd, sizeof(t_data));
			fc->lst_cmd->cmd = ft_strdup(tmp->cmd);
			fc->lst_cmd->nb = tmp->nb;
			dprintf(2, "nb: %d\t", tmp->nb);
			dprintf(2, "cmd: %s\n", fc->lst_cmd->cmd);
		}
		if (fc->lst_cmd && last_nb && first_nb != tmp->nb)
		{
			fc->lst_cmd = hist_add(fc->lst_cmd);
			fc->lst_cmd->cmd = ft_strdup(tmp->cmd);
			fc->lst_cmd->nb = tmp->nb;
			dprintf(2, "nb: %d\t", tmp->nb);
			dprintf(2, "cmd: %s\n", fc->lst_cmd->cmd);
		}
		if (fc->lst_cmd && (!last_nb || first_nb == last_nb || last_nb == tmp->nb))
			break ;
		tmp = fc->lst_cmd && last_nb > first_nb ? tmp->next : tmp->prev;
	}
	return (0);
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
	while(args && args[++fc->i] && fc->nb < 2)
	{
		if ((args[fc->i][0] == '-' && ft_isdigit(args[fc->i][1])) ||
		ft_isdigit(args[fc->i][0]))
			!fc->nb ? (fc->first = ft_itoa(ft_atoi(args[fc->i])))
			: (fc->last = ft_itoa(ft_atoi(args[fc->i])));
		else
			!fc->nb ? (fc->first = ft_strdup(args[fc->i]))
			: (fc->last = ft_strdup(args[fc->i]));
		fc->nb++;
	}
	if (fc->first && builtin_fc_search_first_occurence(fc, shell->hist))
		return (1);
//	dprintf(2, "ops: %s\n", fc->op);
//	dprintf(2, "first: %s\n", fc->first);
//	dprintf(2, "last: %s\n", fc->last);
	//ret = shell();
	return (0);
}
