/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin_free.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 23:46:11 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/01 12:02:31 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/libft.h"

int		ft_strjoin_free(char **s1, const char *s2)
{
	char *tmp;

	if (!(*s1))
	{
		if (!(*s1 = ft_strdup(s2)))
			return (0);
	}
	else
	{
		if (!(tmp = ft_strjoin(*s1, s2)))
			return (0);
		ft_strdel(s1);
		*s1 = tmp;
	}
	return (1);
}
