/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 19:56:27 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 11:00:07 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		builtin_echo(char **cmd)
{
	int		i;
	BOOL	newl;

	newl = 1;
	i = 1;
	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
	{
		newl = 0;
		i = 2;
	}
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "") != 0)
			ft_dprintf(1, "%s", cmd[i]);
		i++;
		if (cmd[i])
			ft_dprintf(1, " ");
	}
	if (newl)
		write(1, "\n", 1);
	return (0);
}
