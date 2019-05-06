/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_alias.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 23:11:41 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 23:11:44 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

char	*shell_alias_remplace(char *shell_str, int i, char *alias,
									char *alias_value)
{
	char	*begin;
	char	*after;
	char	*tmp;

	begin = ft_strsub(shell_str, 0, i);
	tmp = shell_str + i + ft_strlen(alias);
	after = ft_strsub(tmp, 0, ft_strlen(tmp));
	tmp = shell_str;
	shell_str = ft_strjoin_mltp(3, begin, alias_value, after);
	ft_strdel(&begin);
	ft_strdel(&tmp);
	ft_strdel(&after);
	return (shell_str);
}

char	*alias_check_list(char *alias, char **shell_alias)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell_alias && shell_alias[i])
	{
		tmp = get_var(shell_alias[i]);
		if (ft_strcmp(tmp, alias) == 0)
		{
			ft_strdel(&tmp);
			tmp = get_value(shell_alias[i]);
			ft_strdelchar(&tmp, '\'');
			tmp[ft_strlen(tmp) - 1] = '\0';
			return (tmp);
		}
		ft_strdel(&tmp);
		i++;
	}
	return (NULL);
}

void	free_alias(t_alias **a)
{
	if (*a)
	{
		ft_strdel(&(*a)->tmp);
		ft_strdel(&(*a)->tmp2);
		ft_strdel(&(*a)->alias);
		ft_strdel(&(*a)->last_alias);
		free(*a);
	}
}

int		shell_alias_remplace_and_check_loop(t_alias *a, char **str, char **al)
{
	if (a->last_alias && ft_strcmp(a->last_alias, a->alias) == 0)
	{
		*str = shell_alias_remplace(*str, a->i, a->tmp, a->last_alias);
		free_alias(&a);
		return (1);
	}
	ft_strdel(&a->last_alias);
	a->last_alias = ft_strdup(a->tmp);
	a->aliased = 1;
	*str = shell_alias_remplace(*str, a->i, a->tmp, a->alias);
	if ((a->tmp2 = alias_check_list(a->alias, al)) ||
		a->alias[ft_strlen(a->alias) - 1] == ' ')
	{
		ft_strdel(&a->tmp2);
		a->aliased = 0;
	}
	ft_strdel(&a->alias);
	return (0);
}

char	*shell_alias(char *str, char **shl_al)
{
	t_alias	*a;

	a = ft_memalloc(sizeof(t_alias));
	while (str[a->i])
	{
		a->len = (int)len_arg(str + a->i, ' ');
		a->tmp = ft_strsub(str, a->i, a->len);
		if (ft_strcmp(a->tmp, "alias") == 0 || !ft_strcmp(a->tmp, "unalias"))
			break ;
		if (str[a->i] == ';')
			a->aliased = 0;
		if (a->aliased == 0 && (a->alias = alias_check_list(a->tmp, shl_al)))
		{
			if (shell_alias_remplace_and_check_loop(a, &str, shl_al))
				return (str);
		}
		else if (a->len > 0)
			a->i = a->i + a->len;
		else
			a->i++;
		ft_strdel(&a->tmp);
	}
	free_alias(&a);
	return (str);
}
