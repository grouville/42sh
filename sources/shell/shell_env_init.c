/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_env_init.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/13 17:57:01 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/01 23:08:02 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** Lorsqu'on lance shell, OLDPWD ne doit pas exister, on le del de dup_envp
*/

int		check_if_env_var_existing(char **env, char *var)
{
	int		i;
	char	*env_var;

	i = -1;
	while (env[++i])
	{
		env_var = get_var(env[i]);
		if (env_var && !(ft_strcmp(var, env_var)))
		{
			ft_strdel(&env_var);
			return (1);
		}
		ft_strdel(&env_var);
	}
	return (0);
}

void	get_env_path_from_file(char **path, char *file)
{
	int		fd;
	char	*line;
	int		next_path;

	line = NULL;
	next_path = 0;
	if ((fd = open(file, O_RDONLY)) > -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (next_path || (!next_path && *path))
				ft_strjoin_free(path, ":");
			ft_strjoin_free(path, line);
			next_path = 1;
			ft_strdel(&line);
		}
		close(fd);
	}
}

char	**init_env_path(char **envp)
{
	char **new_envp;
	char *path;

	path = NULL;
	get_env_path_from_file(&path, "/etc/paths");
	get_env_path_from_file(&path, "/etc/paths.d/munki");
	new_envp = append_key_env(envp, "PATH", path);
	ft_strdel(&path);
	return (new_envp);
}

char	**init_set_env_variables(char **envp)
{
	char *tmp;

	tmp = get_user_name();
	if (envp && !check_if_env_var_existing(envp, "PATH"))
		envp = init_env_path(envp);
	if (envp && !check_if_env_var_existing(envp, "SHLVL"))
		envp = append_key_env(envp, "SHLVL", "1");
	if (envp && !check_if_env_var_existing(envp, "HOME"))
		envp = append_key_env(envp, "HOME", tmp);
	else if (envp && tmp && ft_strcmp(get_envp(envp, "HOME"), tmp))
	{
		envp = rmv_key_env(envp, "HOME");
		envp = append_key_env(envp, "HOME", tmp);
	}
	ft_strdel(&tmp);
	return (envp);
}

char	**init_env(char **envp)
{
	int		i;
	int		j;
	char	*var;

	i = -1;
	envp = init_set_env_variables(envp);
	while (envp[++i] && (j = -1) == -1)
	{
		if ((var = get_var(envp[i])) && !(ft_strcmp(var, "SHLVL")))
		{
			while (envp[i][++j] != '=')
				;
			ft_strdel(&var);
			var = ft_itoa(ft_atoi(envp[i] + j + 1) + 1);
			ft_strdel(&envp[i]);
			envp[i] = ft_strjoin_mltp(3, "SHLVL", "=", var);
			ft_strdel(&var);
		}
		ft_strdel(&var);
	}
	return (envp);
}
