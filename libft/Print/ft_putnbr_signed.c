/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:27:48 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:27:48 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "print.h"

int		ft_putnbr_signed(intmax_t nb)
{
	int			len_nb;

	len_nb = 0;
	if (nb == (-9223372036854775807 - 1))
	{
		len_nb += ft_putnbr_signed(-922337203685477580);
		nb = 8;
	}
	if (nb < 0)
	{
		len_nb += ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		len_nb += ft_putnbr_signed(nb / 10);
		len_nb += ft_putnbr_signed(nb % 10);
	}
	else
		len_nb += ft_putchar(nb + 48);
	return (len_nb);
}
