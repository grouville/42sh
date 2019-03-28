/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_alias.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/04 22:15:59 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 02:06:42 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

static int		builtin_alias_init(char **args, char **op)
{
	int i;

	i = 0;
	if (args[0] && (i = builtin_get_options(op, args, "p")) == -1)
	{
		ft_dprintf(2, "42sh: alias: -%s: invalid option\nalias: usage:"
		" alias [-p] [name[=value] ... ]\n", *op);
		ft_strdel(op);
		return (-1);
	}
	return (i);
}

static int		builtin_alias_found(char *arg, char **alias, char *val)
{
	char *cmd;

	if (val && !ft_strncmp(*alias, arg, ft_strlen(arg) - ft_strlen(val)))
	{
		ft_strdel(alias);
		cmd = ft_strsub(arg, 0, ft_strlen(arg) - (ft_strlen(val) + 1));
		*alias = ft_strjoin_mltp(5, cmd, "=", "'", val, "'");
		ft_strdel(&cmd);
		return (1);
	}
	else if (!val && !ft_strncmp(arg, *alias, ft_strlen(arg)))
	{
		ft_dprintf(1, "alias %s\n", *alias);
		return (1);
	}
	return (0);
}

static void		builtin_alias_print(char **alias)
{
	while (*alias)
		ft_dprintf(1, "alias %s\n", *alias++);
}

static void		builtin_alias_not_found(char *arg, char ***alias, char *vl)
{
	char *cmd;
	char **alias_tmp;

	if (!vl || arg[0] == '=')
		ft_dprintf(2, "42sh: alias: %s: not found\n", arg);
	else
	{
		alias_tmp = ft_arrnew(ft_arrlen(*alias) + 1);
		ft_arrcpy(alias_tmp, *alias);
		alias_tmp[ft_arrlen(*alias)] = ft_strjoin_mltp(5, (
		cmd = ft_strsub(arg, 0, ft_strlen(arg) -
		(ft_strlen(vl) + 1))), "=", "'", vl, "'");
		free(*alias);
		ft_strdel(&cmd);
		*alias = alias_tmp;
	}
}

int				builtin_alias(char ***al, char **ag)
{
	int		d[3];
	char	**al_t;
	char	*tl[2];

	tl[0] = NULL;
	if ((d[2] = builtin_alias_init(ag, &(tl[0])) - 1) == -2)
		return (1);
	if (!(d[1] = 0) && ((!ag[0] || (tl[0] && ft_strchr(tl[0], 'p')))))
		builtin_alias_print(*al);
	if (!tl[0] || ft_strchr(tl[0], 'p'))
		while (ag[++d[2]] && (al_t = *al))
		{
			d[0] = 1;
			tl[1] = ft_strchr(ag[d[2]], '=') ? ft_strchr(ag[d[2]], '=') + 1 : 0;
			while (*al_t)
			{
				if (builtin_alias_found(ag[d[2]], &*al_t, tl[1]) && !(d[0] = 0))
					break ;
				al_t++;
			}
			if ((!tl[1] && d[0] && (d[1] = 1)) || (tl[1] && d[0]))
				builtin_alias_not_found(ag[d[2]], al, tl[1]);
		}
	ft_strdel(&(tl[0]));
	return (d[1]);
}
