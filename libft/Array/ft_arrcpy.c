/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_arrcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/19 11:51:13 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/21 18:11:47 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "array.h"

char	**ft_arrcpy(char **arr_dst, char **arr_src)
{
	char **ret;

	ret = arr_dst;
	while (arr_dst && arr_src && *arr_src)
		*arr_dst++ = *arr_src++;
	return (arr_dst);
}
