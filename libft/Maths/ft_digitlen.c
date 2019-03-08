/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_digitlen.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/14 01:32:03 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/14 01:32:03 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "maths.h"

int		ft_digitlen(intmax_t n)
{
	size_t				res;

	res = 0;
	if (n < 0)
	{
		res++;
		n *= -1;
	}
	if (n > 9)
	{
		res++;
		return (res + ft_digitlen(n / 10));
	}
	res++;
	return (res);
}
