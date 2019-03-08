/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arrlen.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 19:58:41 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/21 20:06:22 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/array.h"

int		ft_arrlen(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
