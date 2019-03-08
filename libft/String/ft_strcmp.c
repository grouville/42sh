/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:28:26 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:28:26 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/string.h"

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

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1++ - *s2++ != 0)
			return (*(unsigned char *)--s1 - *(unsigned char *)--s2);
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
