/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putwstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/13 23:59:35 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/13 23:59:37 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/print.h"

/*
** La valeur retournée correspond au nombre d'octet print (≠ nbr caractere)
*/

int	ft_putwstr(wchar_t const *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (*s)
			i += ft_putwchar(*s++);
	}
	return (i);
}
