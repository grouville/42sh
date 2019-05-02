/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd_tools.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/08 13:19:17 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 08:02:43 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** Vérifie que var contient seulement des caractère autorisé [a-zA-Z0-9_]
** Si var est un seul digit c'est invalid
*/

BOOL	is_var(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	if (i == 1 && ft_isdigit(arg[0]))
		return (0);
	return (1);
}

/*
** se poisitonne au dernier '/' et remet a '\0' jusqu'a la fin
** sauf si on est a la racine
*/

char	*cd_rmv_last_path(char *cur_dir)
{
	char *tmp;

	if (ft_strlen(cur_dir) > 1)
	{
		tmp = ft_strchr(cur_dir, '/') + 1;
		while (ft_strchr(tmp, '/'))
			tmp = ft_strchr(tmp, '/') + 1;
		while (*tmp)
			*tmp++ = '\0';
	}
	return (cur_dir);
}
