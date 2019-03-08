/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:27:23 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:27:23 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "memory.h"

/*
** Copie len octet(s) de l'int c dans *b
*/

void	*ft_memset(void *b, int c, size_t len)
{
	void	*tmp_b;

	tmp_b = b;
	while (len--)
		*(unsigned char *)b++ = (unsigned char)c;
	return (tmp_b);
}
