/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 13:54:45 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 06:12:10 by dewalter    ###    #+. /#+    ###.fr     */
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

int		builtin_fc(char **args, t_shell *shell)
{
	t_fc	*fc;

	(void)shell;
	if (!(fc = malloc(sizeof(t_fc))))
		exit(EXIT_FAILURE);
	ft_bzero(fc, sizeof(t_fc));
	fc->i = -1;
	if (args[0] && args[0][0] == '-' && !ft_isdigit(args[0][1]) && (fc->i = builtin_fc_init_op(args, &fc->op) - 1) == -2)
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
	//if ()
	dprintf(2, "ops: %s\n", fc->op);
	dprintf(2, "first: %s\n", fc->first);
	dprintf(2, "last: %s\n", fc->last);
	//ret = shell();
	return (0);
}
