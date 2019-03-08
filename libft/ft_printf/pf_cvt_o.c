/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cvt_oO.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/24 18:11:01 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/24 18:11:01 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

void		ft_cast_o(t_pf_prints *print, t_pf_fields *fields)
{
	if (fields->size == 'h' && fields->type == 'o')
		print->data = (void *)ft_utoa((unsigned short int)print->data, 8);
	else if (fields->size == 'H' && fields->type == 'o')
		print->data = (void *)ft_utoa((unsigned char)print->data, 8);
	else if (ft_strchr("lLjz", fields->size))
		print->data = (void *)ft_utoa((uintmax_t)print->data, 8);
	else if (fields->type == 'o')
		print->data = (void *)ft_utoa((unsigned int)print->data, 8);
	else
		print->data = (void *)ft_utoa((intmax_t)print->data, 8);
}

t_pf_prints	pf_cvt_o(t_pf_prints *print, t_pf_fields *fields)
{
	int		calc;

	if (fields->diese && (intmax_t)print->data != 0)
		print->zero_bfr = 1;
	if ((intmax_t)print->data == 0 && fields->point && !fields->diese)
		print->data = (void *)ft_strnew(1);
	else
		ft_cast_o(print, fields);
	if (fields->precision > ft_strlen((char *)print->data))
		print->zero_bfr = fields->precision - ft_strlen((char *)print->data);
	calc = ft_strlen((char *)print->data) + print->zero_bfr;
	if (fields->diese && fields->width > (calc + 2) && !fields->moins)
		print->space_bfr = fields->width - calc;
	else if (fields->diese && fields->width > (calc + 2) && fields->moins)
		print->space_aftr = fields->width - calc;
	else if (fields->width > calc && fields->moins)
		print->space_aftr = fields->width - calc;
	else if (fields->width > calc && !fields->moins)
		print->space_bfr = fields->width - calc;
	if (print->space_bfr && fields->zero && !fields->precision)
	{
		print->zero_bfr = print->space_bfr;
		print->space_bfr = 0;
	}
	return (*print);
}
