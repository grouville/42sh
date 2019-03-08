/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_split_envsub.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 19:05:07 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 19:05:07 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Include/shell.h"

int				shell_argsub_env(char **arg, int i, char **envp, char **envl)
{
	char	*tmp;
	char	*var;
	size_t	len;

	tmp = *arg + i;
	len = 1;
	while (tmp[len] && (ft_isalnum(tmp[len]) || tmp[len] == '_' ||
			tmp[len] == '?'))
		len++;
	if (len == 1)
		return (i);
	tmp[0] = '\0';
	tmp = ft_strsub(tmp, 1, len - 1);
	var = get_envp(envp, tmp) ? get_envp(envp, tmp) : get_envp(envl, tmp);
	ft_strdel(&tmp);
	if (var == NULL)
		tmp = ft_strjoin_mltp(2, *arg, *arg + i + len);
	else
		tmp = ft_strjoin_mltp(3, *arg, var, *arg + i + len);
	ft_strdel(arg);
	*arg = tmp;
	if (var == NULL)
		return (i - 1);
	else
		return (i + ft_strlen(var) - 1);
}

struct passwd	*shell_struct_user(char **arg)
{
	char			*tmp;
	char 			*name;
	struct passwd	*user;
	uid_t			uid;

	if ((*arg)[1] == '/' || (*arg)[1] == '\0')
	{
		uid = getuid();
		user = getpwuid(uid);
	}
	else
	{
		name = ft_strdup(*arg + 1);
		if ((tmp = ft_strchr(name, '/')))
			tmp[0] = '\0';
		user = getpwnam(name);
		ft_strdel(&name);
	}
	return (user);
}

void			shell_check_tilde(char **arg)
{
	char			*tmp;
	struct passwd	*user;

	user = shell_struct_user(arg);
	if (user)
	{
		if ((tmp = ft_strchr(*arg, '/')))
			tmp = ft_strjoin(user->pw_dir, tmp);
		else
			tmp = ft_strdup(user->pw_dir);
		ft_strdel(arg);
		*arg = tmp;
	}
}

/*
** Remplace le tilde si existant
** Remplace les var d'environnements
*/

void			shell_envpsub(char **arg, char **envp, char **envl)
{
	int		i;
	char	quote;

	if ((*arg)[0] == '~')
		shell_check_tilde(arg);
	quote = *arg && ft_strchr("\"'", *arg[0]) ? (char)*arg[0] : (char)' ';
	i = (quote == ' ') ? 0 : 1;
	while (*arg && (*arg)[i])
	{
		if ((*arg)[i] == '\\' && ft_strlen(*arg) > (i + 2) && quote != '\'')
			i += 2;
		if (ft_strchr("'\"", (*arg)[i]) && quote == ' ')
			quote = (*arg)[i];
		else if ((*arg)[i] == quote && quote != ' ')
			quote = ' ';
		if ((*arg)[i] == '$' && quote != '\'')
			i = shell_argsub_env(arg, i, envp, envl);
		i++;
	}
}
