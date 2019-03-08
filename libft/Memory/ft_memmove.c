/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:27:17 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:27:17 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "memory.h"

/*
** Copie n octet de src dans dst
*/

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	void	*temp_dst;

	temp_dst = dst;
	if (dst <= src || (unsigned char *)dst > ((unsigned char *)src + n))
		return (ft_memcpy(dst, src, n));
	else
	{
		dst = (unsigned char *)dst + n - 1;
		src = (unsigned char *)src + n - 1;
		while (n--)
			*(unsigned char *)dst-- = *(unsigned char *)src--;
	}
	return (temp_dst);
}
