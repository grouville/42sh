/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_type.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/15 14:38:10 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/15 14:38:10 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	ft_type_str(va_list ap, char type)
{
	intmax_t data;

	if (type == 's')
		data = (intmax_t)va_arg(ap, char*);
	else if (type == 'S')
		data = (intmax_t)va_arg(ap, wchar_t*);
	else
		return (0);
	return (data);
}

intmax_t	ft_type_char(va_list ap, char type)
{
	intmax_t data;

	if (type == 'C')
		data = (intmax_t)va_arg(ap, wchar_t);
	else if (type == 'c')
		data = (intmax_t)va_arg(ap, int);
	else if (type == '%')
		data = '%';
	else
		return (0);
	return (data);
}

intmax_t	ft_type_int(va_list ap, char type)
{
	intmax_t data;

	if (ft_strchr("oOuUxXb", type))
		data = (intmax_t)va_arg(ap, uintmax_t);
	else if (ft_strchr("dDi", type))
		data = (intmax_t)va_arg(ap, intmax_t);
	else if (type == 'p')
		data = (intmax_t)va_arg(ap, void *);
	else
		return (0);
	return (data);
}

void		ft_type_wildcard(va_list ap, t_pf_fields *fields)
{
	if (fields->width == -1)
		fields->width = va_arg(ap, int);
	if (fields->width < 0)
	{
		fields->moins = 1;
		fields->width *= -1;
	}
	else if (fields->wldcrd_width)
		va_arg(ap, int);
	if (fields->precision == -1)
		fields->precision = va_arg(ap, int);
	if (fields->precision < 0)
		fields->point = 0;
	if (fields->precision < 0)
		fields->precision = 0;
}

intmax_t	pf_type(va_list ap, t_pf_fields *fields)
{
	intmax_t data;

	ft_type_wildcard(ap, fields);
	if (ft_strchr("cC%", fields->type))
		data = ft_type_char(ap, fields->type);
	else if (ft_strchr("sS", fields->type))
		data = ft_type_str(ap, fields->type);
	else if (ft_strchr("dDioOuUxXpb", fields->type))
		data = ft_type_int(ap, fields->type);
	else
		return (0);
	return (data);
}
