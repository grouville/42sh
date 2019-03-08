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

#include "../../Include/shell.h"

int		is_only_digit(char *arg)
{
	int i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (0);
	}
	return (ft_atoi(arg));
}

/*
** return -2 si fail (pas d'exit) ou la valeur de retour
** -1 pour pas que shell_process return -1
*/

int		builtin_exit(char **cmd)
{
	unsigned char ret;

	if (cmd[1] == NULL)
		return (0);
	else if (!is_only_digit(cmd[1]))
	{
		ft_dprintf(2, "42sh: exit: %s: numeric argument required\n", cmd[1]);
		return (2);
	}
	else if (cmd[2] != NULL)
	{
		ft_dprintf(2, "42sh: exit: too many arguments\n");
		return (-2);
	}
	else
	{
		ret = (unsigned char)ft_atoi(cmd[1]);
		return (ret);
	}
}
