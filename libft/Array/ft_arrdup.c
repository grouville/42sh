/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_arrdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 19:55:44 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 19:55:52 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "array.h"

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * ft_arrlen(arr) + sizeof(char *));
	i = 0;
	while (arr[i] != NULL)
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
