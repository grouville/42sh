/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/21 18:06:23 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/21 18:06:27 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

/*
** pf_parse_correct, ft_undef_char, ft_undef_beha sont des fonctions
** qui ont pour role de strictement respecter printf et ses cas non définis.
** Elles sont inutiles si on utilise correctement printf
*/

void	pf_parse_correct(t_pf_fields *fields, char type, const char *str)
{
	while (*str != type)
	{
		if (*str == '#')
			fields->diese = 1;
		if (*str == '+')
			fields->plus = 1;
		if (*str == '-')
			fields->moins = 1;
		if (*str == '*' && *(str - 1) == '.')
			fields->wldcrd_prec = 1;
		str++;
	}
	if (fields->moins && fields->zero)
		fields->zero = 0;
	if (fields->space && fields->plus)
		fields->space = 0;
	if (fields->space && (fields->plus || ft_strchr("uUoO", fields->type)))
		fields->space = 0;
	if (fields->zero && fields->point && !ft_strchr("cCsS%", fields->type)
		&& !fields->wldcrd_prec)
		fields->zero = 0;
	if (fields->type == 's' && ft_strchr("lL", fields->size))
		fields->type = 'S';
}

int		ft_undef_char(const char **format, int fd)
{
	t_pf_fields	fields;
	intmax_t	data;
	t_pf_prints	print;
	int			len_print;

	(*format)++;
	fields = pf_fields_reset();
	pf_parse_flags(&fields, format);
	fields.width = ft_strnbr(*format);
	if (fields.width)
		(*format) += ft_lenint(fields.width);
	while (ft_strchr(PRINTF_ALL_FIELDS, **format))
	{
		if (**format == '-')
			fields.moins = 1;
		(*format)++;
	}
	data = (intmax_t)**format;
	(*format)++;
	fields.type = 'c';
	print = pf_convert(&data, &fields);
	len_print = pf_print_field(&print, &fields, fd);
	return (len_print);
}

int		ft_undef_beha(const char **format)
{
	int	i;

	if (ft_strlen(*format) == 1)
	{
		*format += 1;
		return (1);
	}
	i = 1;
	while (ft_strchr(PRINTF_ALL_FIELDS, (*format)[i]))
		i++;
	if ((!ft_strchr(PRINTF_TYPE, (*format)[i]) &&
		ft_strchr(PRINTF_ALL_FIELDS, (*format)[i])) ||
		(*format)[i] == '\0')
	{
		*format += i;
		return (1);
	}
	else if (!ft_strchr(PRINTF_TYPE, (*format)[i]) &&
		!ft_strchr(PRINTF_ALL_FIELDS, (*format)[i]))
		return (-1);
	return (0);
}

/*
** Attention : les fd sont prit en compte seulemt pour %s et %c
*/

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list		ap;
	t_pf_fields	fields;
	intmax_t	data;
	t_pf_prints	print;
	int			len_print;

	va_start(ap, format);
	len_print = 0;
	while (*format)
	{
		if (*format == '%' && ft_undef_beha(&format) == 0)
		{
			format++;
			fields = pf_parse(&format);
			data = pf_type(ap, &fields);
			print = pf_convert(&data, &fields);
			len_print += pf_print_field(&print, &fields, fd);
		}
		else if (*format == '%' && ft_undef_beha(&format) == -1)
			len_print += ft_undef_char(&format, fd);
		else if (ft_strlen(format) >= 1)
			len_print += ft_putchar_fd(*format++, fd);
	}
	va_end(ap);
	return (len_print);
}
