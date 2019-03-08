/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrncpy.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/15 19:28:56 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/15 19:29:05 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/string.h"

/*
** Copie au max {len} charactere de {src} dans {dst}
** Si {src} est plus petit que {len} on finit de renplir avec '\0'
** Si {src} est plus grand que {len}, {dst} ne sera pas finit par
** l'octet '\0' de {src}
**
** Remarque :
** {ret} permet de garder le pointeur du tableau en position 0 lors du return
*/

wchar_t		*ft_wstrncpy(wchar_t *dst, const wchar_t *src, size_t len)
{
	wchar_t *ret;

	ret = dst;
	while (len)
	{
		if (*src)
		{
			if (len >= (size_t)ft_size_wchar(*src))
				*dst++ = *src;
			if (len >= (size_t)ft_size_wchar(*src))
				len = len - ft_size_wchar(*src);
			else
				len = 0;
			src++;
		}
		else
			*dst++ = '\0';
	}
	return (ret);
}
