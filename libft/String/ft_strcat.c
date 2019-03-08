/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcat.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:28:13 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:28:13 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/string.h"

/*
** Ajoute {s2} a la fin de {s1} puis ajoute '\0'.
** {s1} doit etre assez grand.
*/

char	*ft_strcat(char *dst, const char *src)
{
	size_t	i;

	i = ft_strlen(dst);
	ft_strcpy(&dst[i], src);
	return (dst);
}
