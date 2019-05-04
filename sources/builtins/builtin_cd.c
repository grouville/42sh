/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/06 23:35:03 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 00:08:55 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** Supprime les doublons de / et .
** /fld1///fld2/././fld3 --> /fld1/fld2/fld3
*/

void	cd_clean_path(char *pwd)
{
	int		i;
	char	*ptn;

	i = 0;
	while (pwd && pwd[i])
	{
		ptn = pwd + i;
		if (pwd[i] == '/' && pwd[i + 1] == '/')
			ft_strdelchar(&ptn, '/');
		else if (pwd[i] == '/' && pwd[i + 1] == '.' && (i + 2) < ft_strlen(pwd)
				&& pwd[i + 2] == '/')
		{
			ft_strdelchar(&ptn, '/');
			ft_strdelchar(&ptn, '.');
		}
		else
			i++;
	}
	i--;
	while (pwd && ft_strchr("./ ", pwd[i]) && i > 0)
		pwd[i--] = '\0';
}

BOOL	cd_is_recheable(char **envp, char *path, char *dir)
{
	if (!path || access(path, X_OK) == -1)
	{
		write(2, "42sh: cd: ", 10);
		if (path && path[0] == '\0' && !get_envp(envp, "HOME"))
			write(2, "$HOME env not set\n", 18);
		else if (access(path, F_OK) == 0 && access(path, X_OK) == -1)
		{
			write(2, path, (size_t)ft_strlen(path));
			write(2, ": Permission denied\n", 20);
		}
		else if (dir)
		{
			write(2, dir, (size_t)ft_strlen(dir));
			write(2, ": No such directory\n", 20);
		}
		return (0);
	}
	return (1);
}

/*
** abs_path --> option P
*/

int		cd_move(char *path_dest, char *dir, char ***envp, BOOL abs_path)
{
	char	*cur_dir;
	char	*tmp;

	if (!cd_is_recheable(*envp, path_dest, dir))
	{
		ft_strdel(&path_dest);
		return (0);
	}
	chdir(path_dest);
	if (abs_path)
		cur_dir = get_cur_dir();
	else
		cur_dir = ft_strdup(path_dest);
	ft_strdel(&path_dest);
	tmp = ft_strdup(get_envp(*envp, "PWD"));
	builtin_setenv(envp, "OLDPWD", tmp);
	ft_strdel(&tmp);
	cd_clean_path(cur_dir);
	builtin_setenv(envp, "PWD", cur_dir);
	ft_strdel(&cur_dir);
	return (EXIT_SUCCESS);
}

BOOL	buildin_cd_opt(char **cmd, int *i)
{
	*i = 1;
	while (cmd[*i] != NULL && cmd[*i][0] == '-' && cmd[*i][1] != '\0')
		(*i)++;
	if (cmd[*i - 1][0] == '-' && cmd[*i - 1][ft_strlen(cmd[*i - 1]) - 1] ==
																		'P')
		return (1);
	else
		return (0);
}

int		builtin_cd(char **cmd, char ***envp)
{
	BOOL	abs_path;
	char	*path_dest;
	int		i;
	char	*tmp;

	tmp = NULL;
	abs_path = buildin_cd_opt(cmd, &i);
	path_dest = NULL;
	if (!cmd[i] && get_envp(*envp, "HOME") == NULL)
		write(2, "42sh: cd: HOME not set\n", 23);
	else if (!cmd[i])
		path_dest = ft_strdup(get_envp(*envp, "HOME"));
	else if (ft_strcmp(cmd[i], "-") == 0 && get_envp(*envp, "OLDPWD") == NULL)
		write(2, "42sh: cd: OLDPWD not set\n", 25);
	else if (ft_strcmp(cmd[i], "-") == 0)
		path_dest = ft_strdup(get_envp(*envp, "OLDPWD"));
	else if (ft_strcmp(cmd[i], "..") == 0 &&
						ft_strcmp(tmp = get_cur_dir(), "/") != 0)
		path_dest = ft_strdup(cd_rmv_last_path(tmp));
	else if (ft_strcmp(cmd[i], ".") == 0)
		path_dest = ft_strdup(get_envp(*envp, "PWD"));
	else
		path_dest = ft_strdup(cmd[i]);
	ft_strdel(&tmp);
	return (!path_dest ? 0 : cd_move(path_dest, cmd[i], envp, abs_path));
}
