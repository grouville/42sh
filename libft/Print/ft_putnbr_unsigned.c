/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_unsigned.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/02 12:09:16 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/02 12:09:28 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "print.h"

int		ft_putnbr_unsigned(uintmax_t nb)
{
	int			len_nb;

	len_nb = 0;
	if (nb > 9)
	{
		len_nb += ft_putnbr_unsigned(nb / 10);
		len_nb += ft_putnbr_unsigned(nb % 10);
	}
	else
		len_nb += ft_putchar(nb + 48);
	return (len_nb);
}
