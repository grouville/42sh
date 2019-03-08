/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrsub_free.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/19 12:55:13 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/19 12:55:30 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/string.h"

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

wchar_t		*ft_wstrsub_free(wchar_t *s, unsigned int start, size_t len)
{
	wchar_t *str;

	if (s)
	{
		if (!(str = ft_wstrnew(len)))
		{
			free(s);
			return (NULL);
		}
		while (start--)
			s++;
		ft_wstrncpy(str, s, len);
		free(s);
		str[len] = '\0';
		return (str);
	}
	return (NULL);
}
