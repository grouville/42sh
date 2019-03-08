/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_arrncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 15:07:47 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/21 18:01:57 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "array.h"

char	**ft_arrncpy(char **arr_dst, char **arr_src, size_t len)
{
	char **ret;

	ret = arr_dst;
	while (len--)
		*arr_dst++ = *arr_src++;
	return (ret);
}
