/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnequ.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:29:35 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:29:35 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Compare lexicographiquement s1 et s2 jusqu’à n caractères
** maximum ou bien qu’un ’\0’ ait été rencontré. Si les deux
** chaines sont égales, la fonction retourne 1, ou 0 sinon.
** int	ft_strequ(char const *s1, char const *, size_t n)
*/

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 && s2)
	{
		if (ft_strncmp(s1, s2, n) == 0)
			return (1);
	}
	return (0);
}
