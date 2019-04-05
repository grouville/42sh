/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_exit.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/08 13:41:53 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 13:41:53 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		is_only_digit(char *arg)
{
	int i;

	i = 0;
	while (arg && arg[i])
	{
		if ((arg[i] >= '0' && arg[i] <= '9') || arg[i] == '-')
			i++;
		else
			return (0);
		if ((arg[0] != '-' && i > 18) || (arg[0] == '-' && i > 19))
			return (0);
	}
	return (ft_atoi(arg));
}

/*
** return 1 si exit fail (pas d'exit mais on confirme que c'est un builtin)
** return -1 si exit necessaire et shell->ret à return
*/

int		builtin_exit(t_cmd *elem, t_shell *shell)
{
	unsigned char ret;

	if (elem->args[1] == NULL)
	{
		shell->ret = 0;
		return (-1);
	}
	else if (!is_only_digit(elem->args[1]))
	{
		ft_dprintf(2, "42sh: exit: %s: numeric argument required\n", elem->args[1]);
		shell->ret = 2;
		return (-1);
	}
	else if (elem->args[2] != NULL)
	{
		ft_dprintf(2, "42sh: exit: too many arguments\n");
		elem->ret = EXIT_FAILURE;
		return (1);
	}
	else
	{
		ret = (unsigned char)ft_atoi(elem->args[1]);
		shell->ret = ret;
		return (-1);
	}
}
