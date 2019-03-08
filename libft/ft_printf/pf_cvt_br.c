/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_cvt_br.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/22 00:24:45 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/22 00:24:55 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_size_b(t_pf_prints *print, t_pf_fields *fields)
{
	if (ft_strchr("lLjz", fields->size))
		print->data = (void *)ft_utoa((intmax_t)print->data, 2);
	else
		print->data = (void *)ft_utoa((unsigned int)print->data, 2);
}

t_pf_prints	ft_cvt_b(t_pf_prints *print, t_pf_fields *fields)
{
	int		calc;

	if (fields->diese && (print->data != 0 || fields->type == 'p'))
		print->zero_x_up = 2;
	if (fields->point && !fields->precision && print->data == 0)
		print->data = (void *)ft_strnew(1);
	else
		ft_size_b(print, fields);
	if (fields->precision > ft_strlen((char *)print->data))
		print->zero_bfr = fields->precision - ft_strlen((char *)print->data);
	calc = ft_strlen((char *)print->data) + print->zero_bfr + print->zero_x_up;
	if (!fields->diese && fields->width > calc && !fields->moins)
		print->space_bfr = fields->width - calc;
	if (fields->diese && fields->width > (calc) && !fields->moins)
		print->space_bfr = fields->width - (calc + print->zero_bfr);
	if (!fields->diese && fields->width > calc && fields->moins)
		print->space_aftr = fields->width - calc;
	if (fields->diese && fields->width > (calc) && fields->moins)
		print->space_aftr = fields->width - (calc + print->zero_bfr);
	if (fields->zero && print->space_bfr > 0 && !print->zero_bfr)
	{
		print->zero_bfr = print->space_bfr;
		print->space_bfr = 0;
	}
	return (*print);
}

t_pf_prints	pf_cvt_br(t_pf_prints *print, t_pf_fields *fields)
{
	if (fields->type == 'b')
		return (ft_cvt_b(print, fields));
	else if (fields->type == 'r')
		return (*print);
	else
		return (*print);
}
