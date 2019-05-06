/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_localvar.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 19:14:11 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 07:51:22 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

char		**save_locvars(char **args, int nb_locvar)
{
	char	**ret;
	int		j;

	ret = (char **)malloc(sizeof(char *) * (nb_locvar + 1));
	ret[nb_locvar] = NULL;
	j = 0;
	while (j < nb_locvar)
	{
		ret[j] = ft_strdup(args[j]);
		j++;
	}
	return (ret);
}

char		**del_locvars(char ***args, int i)
{
	int		len;
	char	**ret;
	int		j;

	len = ft_arrlen(*args);
	ret = (char **)malloc(sizeof(char *) * (len - i + 1));
	j = 0;
	while ((*args)[i])
		ret[j++] = ft_strdup((*args)[i++]);
	ret[j] = NULL;
	ft_arrdel(args);
	return (ret);
}

/*
** ajoute les vars local si chaque arg de args sont des déclarations de var
** sinon delete les arg de args qui sont des var {a=123 ls --> ls}
** args_raw permet de checker si l'arg est réellement un var ("arg"=notvar)
*/

int			builtin_localvar(t_cmd *elem)
{
	int		i;
	char	**args;

	if (!(args = elem->args))
		return (0);
	if (!ft_strchr(args[0], '='))
		return (0);
	i = 0;
	while (args[i])
	{
		if ((args[i] && !ft_strchr(args[i], '=')) || (elem->args_raw[i] &&
				!is_var(elem->args_raw[i])))
		{
			elem->envl_exec = save_locvars(args, i);
			dprintf(2, "-<on del args|%s|>\n", args[i]);
			elem->args = del_locvars(&elem->args, i);
			return (0);
		}
		i++;
	}
	return (1);
}
