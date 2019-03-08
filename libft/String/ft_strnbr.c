/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/08 12:28:50 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/08 12:28:53 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/string.h"

/*
** Extract nbr from str and apply atoi to return int
*/

int	ft_strnbr(const char *str)
{
	int		i;
	char	*tmp;
	int		digit;

	i = 0;
	while (ft_strchr("0123456789", str[i]))
		i++;
	ft_strncat(tmp = ft_strnew(i), str, i);
	digit = ft_atoi(tmp);
	ft_strdel(&tmp);
	return (digit);
}
