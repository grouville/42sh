/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 18:02:22 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 14:20:42 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	check_path_loop(char **path_env, char **path, char **str, int *count)
{
	int		j;
	char	*join_slash;
	char	*join_cmd;

	j = 0;
	while (path_env[j])
	{
		join_slash = ft_strjoin(path_env[j], "/");
		join_cmd = ft_strjoin(join_slash, *str);
		free(join_slash);
		if (access(join_cmd, F_OK) == 0)
		{
			if (*count >= 1)
				free(*path);
			*path = ft_strdup(join_cmd);
			(*count)++;
		}
		j++;
		free(join_cmd);
	}
	if (!(*path))
		*path = NULL;
}

int		check_path(char **path_env, char **path, char **str)
{
	int	count;

	count = 0;
	if (path_env != NULL)
	{
		check_path_loop(path_env, path, str, &count);
	}
	return (count);
}

int		ft_usage_is_good(char *limitor, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (ft_strlen(str) > 1)
	{
		if (str[0] == '-' && (i = i + 1))
		{
			while (limitor[++j])
			{
				while (str[i])
				{
					if (limitor[j] == str[i])
						i++;
					else
						break ;
				}
			}
		}
		if (str[i])
			return (1);
	}
	return (0);
}

int			ft_check_arguments(int *i, char **cmd, int *boul, t_shell *env)
{
	while (cmd[*i] && cmd[*i][0] == '-')
	{
		if (ft_usage_is_good("r", cmd[*i]))
		{
			ft_dprintf(1, "bash: hash: %s: invalid option\n", cmd[*i]);
			ft_dprintf(1, "hash: usage: hash [-r] [name ...]\n");
			return (2);
		}
		*boul = TO_RESET;
		(*i)++;
	}
	if (--(*i) && *boul == TO_RESET && env->t)
		delete_hash_table(&(env->t));
	return (0);
}

void		add_binary_to_hash(int *i, char **cmd, t_shell *env,
				char **path)
{
	char **all_paths;

	all_paths = ft_strsplit(get_envp(env->envp, "PATH"), ':');
	while (cmd[++(*i)])
	{
		if (ft_strchr(cmd[*i], '/'))
			;
		else
		{
			if (all_paths)
			{
				check_path(all_paths, path, &(cmd[*i]));
				if (!(*path))
				{
					ft_dprintf(1, "%s", "bash: hash:");
					ft_dprintf(1, "%s: not found\n", cmd[*i]);
				}
				else
				{
					if (!env->t)
						env->t = new_hash_table();
					insert_element(env->t, cmd[*i], *path);
				}
			}
		}
	}
	ft_arrdel(&all_paths);
}

int			ft_builtin_hash(char **cmd, t_shell *env)
{
	int			i;
	int			len;
	int			boul;
	char		*path;

	i = 1;
	path = NULL;
	len = ft_arrlen(cmd);
	boul = NO_RESET;
	if (len == 1)
		ft_print_hash(env);
	else
	{
		if (ft_check_arguments(&i, cmd, &boul, env))
			return (2);
		add_binary_to_hash(&i, cmd, env, &path);
		if (path != NULL)
			free(path);
		path = NULL;
	}
	return (0);
}
