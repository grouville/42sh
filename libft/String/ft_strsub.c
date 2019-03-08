/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:30:00 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:30:00 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Retourne une copie fraiche de {*s} commençant à {start}
** et de longueur {len}.
**
** Si start et len ne désignent pas un tronçon de chaine valide,
** le comportement est indéterminé.
*/

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *str;

	if (s)
	{
		if (!(str = ft_strnew(len)))
			return (NULL);
		while (start--)
			s++;
		ft_strncpy(str, s, len);
		str[len] = '\0';
		return (str);
	}
	return (NULL);
}
