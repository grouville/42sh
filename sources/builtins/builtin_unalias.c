/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unalias.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 11:04:33 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/22 16:21:27 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

static int		builtin_unalias_init(char **args, char ***alias)
{
	int		i;
	char	*op;

	i = 0;
	op = NULL;
	if (!*args || (i = builtin_get_options(&op, args, "a", 0)) == -1)
	{
		if (i == -1)
			ft_dprintf(2, "42sh: unalias: -%s: invalid option\n", op);
		ft_dprintf(2, "unalias: usage: unalias [-a] name [name ...]\n");
		ft_strdel(&op);
		return (-1);
	}
	if (op && ft_strchr(op, 'a'))
	{
		if (**alias)
		{
			ft_arrdel(alias);
			*alias = ft_arrnew(0);
		}
		ft_strdel(&op);
		return (-2);
	}
	ft_strdel(&op);
	return (i);
}

static char		*builtin_unalias_get_alias_name(char *alias)
{
	char *name;

	name = NULL;
	if ((name = ft_strchr(alias, '=')))
		name = ft_strsub(alias, 0, ft_strlen(alias) - ft_strlen(name));
	return (name);
}

static void		builtin_unalias_delete_alias(char ***alias,
				char **name, int index, int *match)
{
	int		start;
	char	**new_alias;

	start = -1;
	new_alias = ft_arrnew(ft_arrlen(*alias) - 1);
	while (++start < index)
		new_alias[start] = ft_strdup((*alias)[start]);
	while ((*alias)[start + 1])
	{
		new_alias[start] = ft_strdup((*alias)[start + 1]);
		start++;
	}
	ft_arrdel(alias);
	ft_strdel(name);
	*alias = new_alias;
	*match = 0;
}

int				builtin_unalias(char ***alias, char **args)
{
	int		d[4];
	char	*name;

	d[3] = 0;
	if ((d[0] = builtin_unalias_init(args, alias) - 1) == -2 || d[0] == -3)
		return (d[0] == -2 ? 1 : 0);
	while (args[++d[0]] && (d[1] = -1) == -1)
	{
		d[2] = 1;
		while ((*alias)[++d[1]])
		{
			if ((name = builtin_unalias_get_alias_name((*alias)[d[1]]))
			&& !ft_strcmp(args[d[0]], name))
			{
				builtin_unalias_delete_alias(alias, &name, d[1], &d[2]);
				break ;
			}
			ft_strdel(&name);
		}
		if (d[2] && (d[3] = 1))
			ft_dprintf(2, "42sh: unalias: %s: not found\n", args[d[0]]);
	}
	return (d[3]);
}
