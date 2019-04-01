/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_tools.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 01:42:49 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 02:07:55 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		builtin_get_options(char **options, char **args, char *possibility,
		int num)
{
	int i[2];

	i[0] = -1;
	while (args[++i[0]] && args[i[0]][0] == '-' && args[i[0]][1] && !(i[1] = 0))
		while (args[i[0]][++i[1]])
			if (!ft_strcmp(args[i[0]], "--") ||
			ft_strchr(possibility, args[i[0]][i[1]]))
			{
				if (!ft_strcmp(args[i[0]], "--"))
					return (i[0] + 1);
				else if (!*options || !ft_strchr(*options, args[i[0]][i[1]]))
					ft_char_join_free(args[i[0]][i[1]], options);
			}
			else
			{
				if (num && i[1] == 1 && ft_isdigit(args[i[0]][i[1]]) &&
				ft_strlen(args[i[0]] + i[1]) ==
				ft_lenint(ft_atoi(args[i[0]] + i[1])))
					return (i[0]);
				ft_strdel(options);
				ft_char_join_free(args[i[0]][i[1]], options);
				return (-1);
			}
	return (i[0]);
}
