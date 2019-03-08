/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_path.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/05 23:20:46 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/05 23:20:46 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../Include/shell.h"

char	*get_var(char *var_key)
{
	int		i;
	char	*ret;

	i = 0;
	while (var_key[i] != '=')
		i++;
	ret = ft_strnew(i);
	ft_strncpy(ret, var_key, i);
	return (ret);
}

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
	else if (exec  && exec[0] == '/' && access(exec, X_OK) != -1)
		ret = ft_strdup(exec);
	else if (exec && exec[0] == '/' && stat(exec, &buffer) == 0 &&
				access(exec, X_OK) == -1)
		ret = (char *)-3;
	else if (exec && ft_strchr(exec, '/'))
		ret = (char *)-2;
	ft_strdel(&exec_path);
	return (ret);
}

/*
** Recherche le bon path de {cmd} dans les differents path de {envp PATH}
** si non trouvé ou PATH inexistant on retourne {cmd}
** /!\ Si un PATH n'a pas les droits mauvais message d'erreur
*/

char	*shell_getpathexec(char *exec, char **envp)
{
	char		*exec_path;
	char		**all_path;
	int			i;

	if (exec == NULL || !ft_strcmp(".", exec) || !ft_strcmp("..", exec))
		return (NULL);
	all_path = ft_strsplit(get_envp(envp, "PATH"), ':');
	exec_path = NULL;
	i = 0;
	while (get_envp(envp, "PATH") && all_path[i] != NULL &&
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
