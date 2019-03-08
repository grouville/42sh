/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrcpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/19 13:40:02 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/19 13:40:12 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Copie {src} dans {dst} (including the terminating `\0' character)
** Remarque :
** {ret} permet de garder le pointeur du tableau en position 0 lors du return
*/

wchar_t		*ft_wstrcpy(wchar_t *dst, const wchar_t *src)
{
	wchar_t *ret;

	ret = dst;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (ret);
}
