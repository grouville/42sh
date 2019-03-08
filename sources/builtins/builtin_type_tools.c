/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_type_tools.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/01 23:21:54 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/16 08:25:54 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Include/shell.h"

int		builtin_get_options(char **options, char **args, char *possibility)
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
				ft_strdel(options);
				ft_char_join_free(args[i[0]][i[1]], options);
				return (-1);
			}
	return (i[0]);
}

int		builtin_type_check_builtin(char *d_name)
{
	if (!ft_strcmp(d_name, "echo") || !ft_strcmp(d_name, "cd") ||
		!ft_strcmp(d_name, "type") || !ft_strcmp(d_name, "unsetenv") ||
		!ft_strcmp(d_name, "setenv") || !ft_strcmp(d_name, "exit") ||
		!ft_strcmp(d_name, "env"))
		return (1);
	return (0);
}

void	builtin_type_display(char *d_name, char *bin, char *op, int mode)
{
	if (!mode)
	{
		if (op && ft_strchr(op, 't') && !ft_strchr(op, 'p')
		&& !ft_strchr(op, 'P'))
			ft_putstr("builtin\n");
		else
			ft_dprintf(1, "%s is a shell builtin\n", d_name);
	}
	else
	{
		if (!op || !ft_strchr(op, 't') || ft_strchr(op, 'P') ||
		ft_strchr(op, 'p'))
		{
			if (!op || (!ft_strchr(op, 'P') && !ft_strchr(op, 'p')))
				ft_dprintf(1, "%s is ", d_name);
			if (bin)
				ft_dprintf(1, "%s/%s\n", bin, d_name);
			else
				ft_putendl(d_name);
		}
		else
			ft_putstr("file\n");
	}
}

int		check_executable_file(char *path)
{
	struct stat stat;

	lstat(path, &stat);
	if (S_ISREG(stat.st_mode) && stat.st_mode & S_IXUSR)
		return (1);
	return (0);
}
