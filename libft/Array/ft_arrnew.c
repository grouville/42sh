/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_arrnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/19 11:43:18 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/19 14:45:44 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "array.h"

char	**ft_arrnew(size_t size)
{
	char **new_array;

	if (!(new_array = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	new_array[size] = NULL;
	return (new_array);
}
