/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrcmp.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/19 14:58:48 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/19 14:58:55 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Compare lexicographiquement s1 et s2. Si les deux chaines
** sont égales, la fonction retourne 1, ou 0 sinon.
**
** Param :
** 1.La première des deux chaines à comparer.
** 2.La seconde des deux chaines à comparer
**
** Retour :
** Renvoi la difference des caractères en int
*/

int	ft_wstrcmp(const wchar_t *s1, const wchar_t *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1++ - *s2++ != 0)
			return (*(wchar_t *)--s1 - *(wchar_t *)--s2);
	}
	return (*(wchar_t *)s1 - *(wchar_t *)s2);
}
