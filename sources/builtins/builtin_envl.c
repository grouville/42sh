/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_envl.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/13 23:03:27 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 23:03:27 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

char	*get_value(char *arg)
{
	int i;

	i = -1;
	while (arg && arg[++i])
		if (arg[i] == '=')
			return (ft_strdup(arg + i + 1));
	return (NULL);
}

int		check_replace_env_variable(char ***env, char *var, char *value)
{
	int		i;
	char	*env_key;

	i = 0;
	while ((*env)[i])
	{
		env_key = get_var((*env)[i]);
		if (!ft_strcmp(var, env_key))
		{
			ft_strdel(&env_key);
			free((*env)[i]);
			(*env)[i] = ft_strjoin_mltp(3, var, "=", value);
			return (1);
		}
		ft_strdel(&env_key);
		i++;
	}
	return (0);
}

int		builtin_env_all(char ***envp, char ***envl, char **args)
{
	char	*var;
	char	*value;

	if (ft_arrlen(args) > 1)
	{
		ft_putstr_fd("42sh: too much arguments\n", 2);
		return (1);
	}
	else
	{
		var = get_var(args[0]);
		value = get_value(args[0]);
		if (ft_strlen(var))
			if (!(check_replace_env_variable(envp, var, value)))
				if (!(check_replace_env_variable(envl, var, value)))
					*envl = append_key_env(*envl, var, value);
		ft_strdel(&var);
		ft_strdel(&value);
	}
	return (0);
}
