/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub_free.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/13 23:38:05 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/20 22:14:00 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Retourne une copie fraiche de {*s} commençant à {start}
** et de longueur {len}. {s} EST DÉTRUIT.
**
** Si start et len ne désignent pas un tronçon de chaine valide,
** le comportement est indéterminé.
*/

char	*ft_strsub_free(char *s, unsigned int start, size_t len)
{
	char *str;

	if (s)
	{
		if (!(str = ft_strnew(len)))
		{
			ft_strdel(&s);
			return (NULL);
		}
		while (start--)
			s++;
		ft_strncpy(str, s, len);
		ft_strdel(&s);
		str[len] = '\0';
		return (str);
	}
	return (NULL);
}
