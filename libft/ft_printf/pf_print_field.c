/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_print_field.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/16 14:11:37 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/16 14:11:40 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

int		ft_print_flags_bfr(t_pf_prints *print)
{
	int len_print;

	len_print = 0;
	while (print->space_bfr > 0)
	{
		len_print += ft_putchar(' ');
		print->space_bfr = print->space_bfr - 1;
	}
	if (print->plus)
		len_print += ft_putchar('+');
	if (print->minus)
		len_print += ft_putchar('-');
	if (print->zero_x)
		len_print += ft_putstr("0x");
	if (print->zero_x_up)
		len_print += ft_putstr("0X");
	while (print->zero_bfr > 0)
	{
		len_print += ft_putchar('0');
		print->zero_bfr = print->zero_bfr - 1;
	}
	return (len_print);
}

int		ft_print_flags_aftr(t_pf_prints *print)
{
	int len_print;

	len_print = 0;
	while (print->space_aftr > 0)
	{
		len_print += ft_putchar(' ');
		print->space_aftr = print->space_aftr - 1;
	}
	while (print->zero_aftr > 0)
	{
		len_print += ft_putchar('0');
		print->zero_aftr = print->zero_aftr - 1;
	}
	return (len_print);
}

int		ft_print_txt(t_pf_prints *print, char c, int len_print, int fd)
{
	len_print += ft_print_flags_bfr(print);
	if (c == 'c' || c == '%')
		len_print += ft_putchar_fd((char)print->data, fd);
	else if (c == 's')
		len_print += ft_putstr_fd((char *)print->data, fd);
	else if (c == 'C')
		len_print += ft_putwchar((wchar_t)print->data);
	else if (c == 'S')
		len_print += ft_putwstr((wchar_t *)print->data);
	len_print += ft_print_flags_aftr(print);
	return (len_print);
}

int		ft_print_int(t_pf_prints *print, t_pf_fields *fields, int len_print)
{
	len_print += ft_print_flags_bfr(print);
	if (ft_strchr("dDi", fields->type) &&
		!(fields->point && print->data == 0))
		len_print += ft_putnbr_signed(ABS((intmax_t)print->data));
	else if (ft_strchr("uU", fields->type) &&
		!(fields->point && print->data == 0))
		len_print += ft_putnbr_unsigned((intmax_t)print->data);
	else if (ft_strchr("xXoOpb", fields->type))
		len_print += ft_putstr((char *)print->data);
	len_print += ft_print_flags_aftr(print);
	return (len_print);
}

int		pf_print_field(t_pf_prints *print, t_pf_fields *fields, int fd)
{
	int len_print;

	len_print = 0;
	if (ft_strchr("cCsS%", fields->type))
		len_print = ft_print_txt(print, fields->type, len_print, fd);
	else if (ft_strchr("dDixXoOuUpb", fields->type))
		len_print = ft_print_int(print, fields, len_print);
	if (ft_strchr("sSxXoOpb", fields->type) && print->free == 1)
		free(print->data);
	return (len_print);
}
