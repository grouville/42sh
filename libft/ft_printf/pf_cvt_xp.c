/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cvt_xX.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/21 18:07:55 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/21 18:07:55 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_size_x(t_pf_prints *print, t_pf_fields *fields)
{
	int calc;

	if (fields->type == 'p')
		print->data = (void *)ft_utoa((unsigned long int)print->data, 16);
	else if (ft_strchr("lLjz", fields->size))
		print->data = (void *)ft_utoa((intmax_t)print->data, 16);
	else
		print->data = (void *)ft_utoa((unsigned int)print->data, 16);
	calc = ft_strlen((char *)print->data);
	if (fields->size == 'h' && calc > 4)
		print->data = (void *)ft_strsub((char *)print->data, calc - 4, 4);
	if (fields->size == 'H' && calc > 2)
		print->data = (void *)ft_strsub((char *)print->data, calc - 2, 2);
}

t_pf_prints	ft_cvt_x_upr(t_pf_prints *print, t_pf_fields *fields)
{
	int		calc;

	if (fields->diese && (print->data != 0 || fields->type == 'p'))
		print->zero_x_up = 2;
	if (fields->point && !fields->precision && print->data == 0)
		print->data = (void *)ft_strnew(1);
	else
		ft_size_x(print, fields);
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

t_pf_prints	ft_cvt_x_lwr(t_pf_prints *print, t_pf_fields *fields)
{
	char *str;

	*print = ft_cvt_x_upr(print, fields);
	if (print->zero_x_up)
	{
		print->zero_x = 1;
		print->zero_x_up = 0;
	}
	str = (char *)print->data;
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
			*str += 32;
		str++;
	}
	return (*print);
}

t_pf_prints	ft_cvt_p(t_pf_prints *print, t_pf_fields *fields)
{
	fields->diese = 1;
	*print = ft_cvt_x_lwr(print, fields);
	return (*print);
}

t_pf_prints	pf_cvt_xp(t_pf_prints *print, t_pf_fields *fields)
{
	if (fields->type == 'x')
		return (ft_cvt_x_lwr(print, fields));
	else if (fields->type == 'X')
		return (ft_cvt_x_upr(print, fields));
	else
		return (ft_cvt_p(print, fields));
}
