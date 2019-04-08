/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_localvar.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 19:14:11 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 19:14:11 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

char		**del_locvars(char **args, int i)
{
	int		len;
	char 	**ret;
	int 	j;

	len = ft_arrlen(args);
	ret = (char **)malloc(sizeof(char *) * (len - i + 1));
	j = 0;
	while (args[i])
		ret[j++] = ft_strdup(args[i++]);
	ret[j] = NULL;
	ft_arrdel(&args);
	return (ret);
}


/*
** ajoute les vars local si chaque arg de args sont des déclarations de var
** sinon delete les arg de args qui sont des var {a=123 ls --> ls}
** args_raw permet de checker si l'arg est réellement un var ("arg"=notvar)
*/

int			builtin_localvar(char ***ptn_args, char **args_raw)
{
	int		i;
	char	**args;

	args = *ptn_args;
	if (!ft_strchr(args[0], '='))
		return (0);
	i = 0;
	while (args[i])
	{
		if (!ft_strchr(args[i], '=') || !is_var(args_raw[i]))
		{
			*ptn_args = del_locvars(args, i);
			return (0);
		}
		i++;
	}
	return (1);
}

