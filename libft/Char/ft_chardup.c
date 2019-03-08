/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_chardup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/24 01:41:55 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/24 01:45:09 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "char.h"

/*
** dupplique dans une chaine  de caractere fraiche le caracte {c} {dup} fois
*/

char	*ft_chardup(char c, int dup)
{
	char *ret;

	ret = ft_strnew(dup);
	while (dup > 0)
		ret[dup-- - 1] = c;
	return (ret);
}
