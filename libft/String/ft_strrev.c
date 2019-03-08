/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrev.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/22 11:47:39 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/22 11:47:39 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Renverse une chaine de caractere
*/

char	*ft_strrev(char *str)
{
	char	swap;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(str);
	while (i < size / 2)
	{
		swap = str[size - (i + 1)];
		str[size - (i + 1)] = str[i];
		str[i] = swap;
		i++;
	}
	return (str);
}
