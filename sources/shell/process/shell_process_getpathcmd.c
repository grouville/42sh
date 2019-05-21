/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_path.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/05 23:20:46 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:21:40 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

char	*get_envp(char **envp, char *var)
{
	char *tmp;

	tmp = NULL;
	while (*envp != NULL)
	{
		tmp = get_var(*envp);
		if (ft_strcmp(tmp, var) == 0)
			break ;
		ft_strdel(&tmp);
		envp++;
	}
	if (*envp != NULL)
		ft_strdel(&tmp);
	else
		return (NULL);
	return (ft_strchr(*envp, '=') + 1);
}

/*
** si l'executable est dans exec (=args[0]) il doit commencer par '/'
** ret :
**  path si exec found
**  -1 si directory
**  -2 si no such file or directory
**  -3 file or path not allowed
*/

char	*check_path_cmd(char *exec_path, char *exec)
{
	char		*ret;
	struct stat	buffer;

	ret = NULL;
	if (exec_path && access(exec_path, X_OK) != -1)
		ret = ft_strdup(exec_path);
	else if (exec_path && stat(exec, &buffer) == 0 &&
				access(exec_path, X_OK) == -1)
		ret = (char *)-3;
	else if (exec && ft_isdir(exec))
		ret = (char *)-1;
	else if (exec && exec[0] == '/' && access(exec, X_OK) != -1)
		ret = ft_strdup(exec);
	else if (exec && exec[0] == '/' && stat(exec, &buffer) == 0 &&
				access(exec, X_OK) == -1)
		ret = (char *)-3;
	else if (exec && ft_strchr(exec, '/'))
		ret = (char *)-2;
	ft_strdel(&exec_path);
	return (ret);
}

char	*shell_check_binaire(char *exec)
{
	char	*tmp;
	char	*path_binaire;

	tmp = get_cur_dir();
	path_binaire = ft_strjoin_mltp(3, tmp, "/", exec + 2);
	ft_strdel(&tmp);
	return (check_path_cmd(path_binaire, exec + 2));
}

/*
** Recherche le bon path de {cmd} dans les differents path de {envp PATH}
** si non trouvé ou PATH inexistant on retourne {cmd}
** /!\ Si un PATH n'a pas les droits mauvais message d'erreur
*/

char	*shell_getpathexec(char *exec, char **all_env)
{
	char		*exec_path;
	char		**all_path;
	int			i;

	if (exec == NULL || !ft_strcmp(".", exec) || !ft_strcmp("..", exec))
		return (NULL);
	if (exec[0] == '.' && exec[1] == '/')
		return (shell_check_binaire(exec));
	all_path = ft_strsplit(get_envp(all_env, "PATH"), ':');
	exec_path = NULL;
	i = 0;
	while (get_envp(all_env, "PATH") && all_path[i] != NULL &&
				!ft_strchr(exec, '/'))
	{
		exec_path = ft_strjoin_mltp(3, all_path[i++], "/", exec);
		if (access(exec_path, X_OK) != -1)
			break ;
		ft_strdel(&exec_path);
	}
	ft_arrdel(&all_path);
	return (check_path_cmd(exec_path, exec));
}
