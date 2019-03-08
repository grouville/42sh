/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cvt_d.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/20 16:57:33 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/20 16:57:33 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_cast_diu(t_pf_prints *print, t_pf_fields *fields)
{
	intmax_t digit;

	if (fields->type == 'u' && !ft_strchr("lLjHz", fields->size))
		digit = (unsigned)print->data;
	else if (fields->size == 'h' && !ft_strchr("UD", fields->type))
		digit = (short int)print->data;
	else if (fields->size == 'H' && fields->type == 'u')
		digit = (unsigned char)print->data;
	else if (fields->size == 'H' && !ft_strchr("UD", fields->type))
		digit = (signed char)print->data;
	else if (fields->size == 0 && !ft_strchr("UD", fields->type))
		digit = (int)print->data;
	else
		digit = (intmax_t)print->data;
	print->data = (void *)digit;
}

int			ft_len(t_pf_prints *print, t_pf_fields *fields)
{
	int len;

	if (print->data == 0 && fields->point)
		len = 0;
	else if ((intmax_t)print->data == (-9223372036854775807 - 1))
		len = 19;
	else
		len = ft_digitlen(ABS((intmax_t)print->data));
	return (len);
}

t_pf_prints	pf_cvt_diu(t_pf_prints *print, t_pf_fields *fields)
{
	int cal;

	ft_cast_diu(print, fields);
	if ((intmax_t)print->data < 0 &&
		(intmax_t)print->data != (-9223372036854775807 - 1) &&
		!ft_strchr("uU", fields->type))
		print->minus = 1;
	if (fields->point && fields->precision > ft_len(print, fields))
		print->zero_bfr = fields->precision - ft_len(print, fields);
	if (fields->plus && (intmax_t)print->data >= 0 &&
		!ft_strchr("uU", fields->type))
		print->plus = 1;
	cal = ft_len(print, fields) + print->zero_bfr + print->plus + print->minus;
	if (!fields->zero && fields->width > cal && !fields->moins)
		print->space_bfr = fields->width - cal;
	else if (fields->zero && fields->width > cal && !fields->point)
		print->zero_bfr = fields->width - cal - fields->space;
	else if (fields->width > cal && fields->moins)
		print->space_aftr = fields->width - cal;
	if (fields->space && print->space_bfr == 0 && print->minus == 0)
		print->space_bfr = 1;
	return (*print);
}
