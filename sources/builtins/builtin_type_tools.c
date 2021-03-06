/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_type_tools.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/01 23:21:54 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 17:34:06 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		builtin_type_check_builtin(char *d_name)
{
	if (!ft_strcmp(d_name, "echo") || !ft_strcmp(d_name, "cd") ||
		!ft_strcmp(d_name, "type") || !ft_strcmp(d_name, "set") ||
		!ft_strcmp(d_name, "unset") || !ft_strcmp(d_name, "exit") ||
		!ft_strcmp(d_name, "export") || !ft_strcmp(d_name, "hash") ||
		!ft_strcmp(d_name, "unset") || !ft_strcmp(d_name, "alias") ||
		!ft_strcmp(d_name, "unalias") || !ft_strcmp(d_name, "test") ||
		!ft_strcmp(d_name, "fg") || !ft_strcmp(d_name, "bg") ||
		!ft_strcmp(d_name, "jobs"))
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
