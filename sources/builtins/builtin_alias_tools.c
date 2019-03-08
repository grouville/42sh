/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_alias_tools.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/23 17:44:11 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/23 18:37:04 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

static int		check_alias(char *alias)
{
	char *name;
	char *val;

	val = NULL;
	if (!alias || alias[0] == '=' ||
	!(val = ft_strchr(alias, '=') ? ft_strchr(alias, '=') + 1 : 0) ||
	(val && val[0] == '\0'))
		return (0);
	if (!(name = ft_strsub(alias, 0, ft_strlen(alias) - (ft_strlen(val) + 1))))
		exit(EXIT_FAILURE);
	if ((ft_strchr(name, ' ') && ft_strchr(name, '\t')) ||
	((ft_strchr(name, '\t') || ft_strchr(val, ' ')) &&
	(val[0] != 39 && val[0] != 34 && val[0] != 96)))
	{
		ft_strdel(&name);
		return (0);
	}
	ft_strdel(&name);
	return (1);
}

char			**builtin_alias_get_alias_from_file(char *file)
{
	t_data	*lt;
	t_data	*lt_tmp;
	char	**alias;
	int		len;

	len = 0;
	lt = init_hist(file);
	while ((lt_tmp = lt) && lt->prev)
		lt = lt->prev;
	while (lt_tmp->next)
	{
		len = check_alias(lt_tmp->cmd) ? len + 1 : len;
		lt_tmp = lt_tmp->next;
	}
	if (!(alias = ft_arrnew(len)))
		exit(EXIT_FAILURE);
	len = 0;
	while (lt)
	{
		check_alias(lt->cmd) ? alias[len++] = lt->cmd : ft_strdel(&lt->cmd);
		lt_tmp = lt->next;
		free(lt);
		lt = lt_tmp;
	}
	return (alias);
}
