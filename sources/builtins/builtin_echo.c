/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_echo.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/07 19:56:27 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 08:03:51 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		check_echo_fdout(t_output *output)
{
	t_output	*find_fd1;
	char		*fd_1;

	fd_1 = NULL;
	find_fd1 = output;
	while (find_fd1)
	{
		if (find_fd1->from == 1)
			fd_1 = find_fd1->to;
		find_fd1 = find_fd1->next;
	}
	if (fd_1 && ft_strlen(fd_1) == 2 && fd_1[1] == '-')
	{
		ft_dprintf(2, "42sh: echo: write error: Bad file descriptor\n");
		return (1);
	}
	else
		return (0);
}

int		builtin_echo(char **cmd, t_output *output)
{
	int		i;
	BOOL	newl;

	if (check_echo_fdout(output))
		return (1);
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
