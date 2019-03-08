/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 21:53:47 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 21:53:47 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Ajoute {src} a la fin de {dst}, qu'importe la taille de {dst}
*/

char	*ft_strcat_free(char *dst, const char *src)
{
	char *retour;

	if (dst && src)
	{
		if (!(retour = ft_strnew(ft_strlen(dst) + ft_strlen(src) + 1)))
			return (NULL);
		ft_strcpy(retour, dst);
		free(dst);
		ft_strcat(retour, src);
		return (retour);
	}
	return (NULL);
}
