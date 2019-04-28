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

#include "shell.h"

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

BOOL		check_env_substitution(char *arg)
{
	int		i;
	char 	quote;

	if (arg[0] == '}')
	{
		ft_dprintf(2, "42sh: ${}: bad substitution\n");
		return (0);
	}
	i = 0;
	while (arg && arg[i] && arg[i] != '}')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '?')
		{
			ft_dprintf(2, "42sh: ${%s: bad substitution\n", arg);
			return (0);
		}
		i++;
	}
	return (1);
}

/*
** Remplace le tilde si existant
** Remplace les var d'environnements
** Retourne 2=bad sub si la var n'est pas correct != (A-Za-z0-9_) ou == ${}
*/

int			shell_envpsub(char **arg, char **envp, char **envl)
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
		{
			if ((*arg)[i + 1] == '{' && !check_env_substitution(*arg + i + 2))
				return (0);
			i = shell_argsub_env(arg, i, envp, envl);
		}
		i++;
	}
	return (1);
}
