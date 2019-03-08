/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_position.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/12 18:13:31 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/23 15:51:41 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

static int		get_row(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			break ;
		i++;
	}
	return (ft_atoi(str + i));
}

static int		get_col(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (i && str[i - 1] == ';' && str[i] >= '0' && str[i] <= '9')
			break ;
	return (ft_atoi(str + i));
}

static int		check_cursor_position(int mode)
{
	int				res;
	char			buf[32];
	unsigned int	i;

	i = 0;
	if (write(1, "\x1b[6n", 4) != 4)
		return (-1);
	while (i < sizeof(buf) - 1)
	{
		if (read(0, buf + i, 1) != 1)
			break ;
		if (buf[i] == 'R')
			break ;
		i++;
	}
	buf[i] = '\0';
	if (buf[0] != 27 || buf[1] != '[')
		return (-1);
	res = mode ? get_row(buf) : get_col(buf);
	return (res);
}

int				get_cursor_position(int mode)
{
	int res;

	res = check_cursor_position(mode);
	return (res == -1 ? get_cursor_position(mode) : res);
}
