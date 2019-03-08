/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrdup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/19 13:30:35 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/19 13:35:38 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Dupplique {s1} dans une nouvelle chaine de char "fraiche"
*/

wchar_t		*ft_wstrdup(const wchar_t *s1)
{
	wchar_t	*copy;

	copy = (wchar_t *)malloc(sizeof(wchar_t) * (ft_wstrlen(s1) + 1));
	if (copy == NULL)
		return (NULL);
	return (ft_wstrcpy(copy, s1));
}
