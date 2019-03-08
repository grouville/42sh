/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:29:30 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:29:30 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Copie au max {len} charactere de {src} dans {dst}
** Si {src} est plus petit que {len} on finit de renplir avec '\0'
** Si {src} est plus grand que {len}, {dst} ne sera pas finit par
** l'octet '\0' de {src}
**
** Remarque :
** {ret} permet de garder le pointeur du tableau en position 0 lors du return
*/

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *ret;

	ret = dst;
	while (len--)
	{
		if (*src)
			*dst++ = *src++;
		else
			*dst++ = '\0';
	}
	return (ret);
}
