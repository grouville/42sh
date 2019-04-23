/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_envsub_tools.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 21:38:37 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 21:38:37 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

size_t 		shell_argsub_len_var(char *argi)
{
	size_t	len;
	size_t	accolade;

	accolade = (argi[1] == '{') ? 1 : 0;
	len = 1 + accolade;
	while (argi[len] && (ft_isalnum(argi[len]) || ft_strchr("_?", argi[len])))
	{
		len++;
		if (argi[len] == '}' && accolade == 1)
		{
			len++;
			break ;
		}

	}
	return (len);
}

char 		*shell_argsub_delaccolade(char *arg)
{
	char *tmp;

	if (arg[0] == '{')
	{
		tmp = ft_strsub(arg, 1, (size_t)ft_strlen(arg) - 2);
		ft_strdel(&arg);
		return (tmp);
	}
	else
		return (arg);
}

char 		*clean_value(char *value)
{
	int 	i;
	char 	*tmp;

	if (value == NULL)
		return (NULL);
	ft_strdelchar(&value, '\'');
	i = 0;
	while (value[i])
	{
		if (value[i] == '\\' && value[i + 1] == 'n')
		{
			value[i] = ' ';
			tmp = value + i;
			ft_strdelchar(&tmp, 'n');
			i -= 2;
		}
		i++;
	}
	tmp = value + i - 1;
	ft_strdelchar(&tmp, '\'');
	return (value);
}

int			shell_argsub_env(char **arg, int i, char **envp, char **envl)
{
	char	*tmp;
	char	*value;
	size_t	len;

	tmp = *arg + i;
	if ((len = shell_argsub_len_var(tmp)) == 1)
		return (i);

	tmp[0] = '\0';
	tmp = shell_argsub_delaccolade(ft_strsub(tmp, 1, len - 1));
	value = get_envp(envp, tmp) ? get_envp(envp, tmp) : get_envp(envl, tmp);
	value = clean_value(ft_strdup(value));
	ft_strdel(&tmp);
	if (value == NULL)
		tmp = ft_strjoin_mltp(2, *arg, *arg + i + len);
	else
		tmp = ft_strjoin_mltp(3, *arg, value, *arg + i + len);
	ft_strdel(arg);
	*arg = tmp;
	len = (size_t)ft_strlen(value);
	ft_strdel(&value);
	if (len == 0)
		return (i - 1);
	else
		return (i + (int)len - 1);
}
