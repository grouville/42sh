/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_utoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/24 16:36:13 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/24 16:36:13 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/maths.h"

/*
** Usigned int TO Array
** Converti un int d'une base donnée dans une chaine de caractère
*/

int		ft_ulen_base(unsigned long long n, unsigned int base)
{
	int	i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char	*ft_utoa(unsigned long long value, unsigned int base)
{
	int		rest;
	char	*str;
	int		i;

	str = ft_strnew(ft_ulen_base(value, base) + 1);
	i = 0;
	while (value >= base)
	{
		rest = value % base;
		str[i++] = (rest > 9) ? ((rest - 10) + 'A') : rest + '0';
		value /= base;
	}
	str[i++] = (value > 9) ? ((value - 10) + 'A') : value + '0';
	str[i] = '\0';
	return (ft_strrev(str));
}
