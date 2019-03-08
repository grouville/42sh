/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrsub.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/15 19:29:54 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/15 19:30:08 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Renvoi une copie de {*s} à partir de l'index {start}
** et de longueur {len} char.
** La chaine de caractère {*s} est detruite.
**
** Param :
** 1.La chaine de caractères dans laquelle chercher le tronçon à copier.
** 2.L’index dans la chaine de caractères où débute le tronçon à copier.
** 3.La longueur du tronçon à copier.
*/

wchar_t		*ft_wstrsub(wchar_t const *s, unsigned int start, size_t len)
{
	wchar_t *str;

	if (s)
	{
		if (!(str = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1))))
			return (NULL);
		while (start--)
			s++;
		ft_wstrncpy(str, s, len);
		str[len] = '\0';
		return (str);
	}
	return (NULL);
}
