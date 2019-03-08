/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:29:21 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:29:21 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Ajoute {n} char de {s2} a la fin de {s1} puis ajoute '\0'.
** {s1} doit etre assez grand.
*/

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char		*retour;
	size_t		i;

	retour = s1;
	while (*s1)
		s1++;
	i = 0;
	while (s2[i] && i < n)
		*s1++ = s2[i++];
	*s1 = '\0';
	return (retour);
}
