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

char 	*value_multiline(char *value)
{
	char 	*ret;

	if (ft_strchr(value, '\n'))
		value = ft_remplace_char_by_str(value, '\n', "\\n");
	if (ft_strchr(value, '\''))
		value = ft_remplace_char_by_str(value, '\'', "\\'");
	ret = ft_strjoin("'", value);
	ft_strdel(&value);
	ft_strjoin_free(&ret, "'");
	return (ret);
}

char	*get_value(char *arg)
{
	int		i;
	char 	*tmp;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '=')
		{
			tmp =  ft_strdup(arg + i + 1);
			if (ft_strchr(tmp, '\n') || ft_strchr(tmp, '\''))
				tmp = value_multiline(tmp);
			return (tmp);
		}
		i++;
	}
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

int		builtin_env_add(char ***envp, char ***envl, char *arg)
{
	char	*var;
	char	*value;

	var = get_var(arg);
	value = get_value(arg);
	if (ft_strlen(var))
		if (!(check_replace_env_variable(envp, var, value)))
			if (!(check_replace_env_variable(envl, var, value)))
				*envl = append_key_env(*envl, var, value);
	ft_strdel(&var);
	ft_strdel(&value);
	return (0);
}
