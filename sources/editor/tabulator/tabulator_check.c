/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator_check.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/06 16:42:37 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/01 21:40:06 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	check_data_with_space_after(char **new_cmd, char *d_name)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp1;

	i = -1;
	j = 0;
	tmp = NULL;
	tmp1 = ft_strdup(d_name);
	while (d_name[++i])
	{
		if (d_name[i] == ' ')
		{
			tmp = ft_strsub(tmp1, 0, j);
			ft_strjoin_free(&tmp, "\\");
			ft_strjoin_free(&tmp, d_name + i);
			ft_strdel(&tmp1);
			tmp1 = ft_strdup(tmp);
			ft_strdel(&tmp);
			j++;
		}
		j++;
	}
	ft_strjoin_free(new_cmd, tmp1);
	ft_strdel(&tmp1);
}

void	check_data_with_space_before(char **path)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp1;

	i = 0;
	j = 0;
	tmp = NULL;
	tmp1 = ft_strdup(*path);
	while ((*path)[i])
	{
		if ((*path)[i] == '\\')
		{
			tmp = ft_strsub(tmp1, 0, j);
			j--;
			ft_strjoin_free(&tmp, *path + i + 1);
			ft_strdel(&tmp1);
			tmp1 = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		i++;
		j++;
	}
	ft_strdel(path);
	*path = tmp1;
}

int		check_if_name_with_new_line(char *name)
{
	int i;

	i = -1;
	while (name[++i])
		if (name[i] == '\n')
			return (1);
	return (0);
}

int		tabulator_check_executable(t_tab *tabu, t_dirent *dirent, char *bin)
{
	t_stat	buf;
	char	*path;
	DIR		*dir;
	int		is_dir;

	is_dir = 0;
	path = build_full_path(bin ? bin : tabu->path, dirent->d_name);
	lstat(path, &buf);
	if ((dir = opendir(path)) && !closedir(dir))
		is_dir = 1;
	ft_strdel(&path);
	if (!tabu->mode || bin || is_dir)
		return (1);
	else if (!bin || tabu->mode == 2)
	{
		if (tabu->path && dirent->d_type == 8 && (buf.st_mode & S_IXUSR))
			return (1);
		else if ((buf.st_mode & S_IFMT) == S_IFDIR || tabu->mode == 2)
			return (1);
	}
	return (0);
}
