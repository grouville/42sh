/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_cvt_s.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/17 14:06:07 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/17 14:06:09 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_strlen_s(t_pf_prints *print, t_pf_fields *fields)
{
	if (fields->type == 's')
		return (ft_strlen((char *)print->data));
	else
		return (ft_wstrlen((wchar_t *)print->data));
}

t_pf_prints	*ft_flags_s(t_pf_prints *print, t_pf_fields *fields)
{
	if (fields->width > ft_strlen_s(print, fields) && !(fields->moins))
	{
		if (fields->zero)
			print->zero_bfr = fields->width - ft_strlen_s(print, fields);
		else
			print->space_bfr = fields->width - ft_strlen_s(print, fields);
	}
	else if (fields->width > ft_strlen_s(print, fields) && fields->moins)
	{
		if (fields->zero)
			print->zero_aftr = fields->width - ft_strlen_s(print, fields);
		else
			print->space_aftr = fields->width - ft_strlen_s(print, fields);
	}
	return (print);
}

t_pf_prints	ft_cvt_s_lwr(t_pf_prints *print, t_pf_fields *fields)
{
	char *str;

	str = (char *)print->data;
	if (fields->point && str == NULL)
		str = ft_strsub("(null)", 0, fields->precision);
	else if (str == NULL)
		str = ft_strdup("(null)");
	else if (fields->point && ft_strlen(str) > fields->precision)
	{
		print->free = 0;
		str = ft_strsub(str, 0, fields->precision);
	}
	else
		print->free = 0;
	print->data = str;
	ft_flags_s(print, fields);
	return (*print);
}

t_pf_prints	ft_cvt_s_upr(t_pf_prints *print, t_pf_fields *fields)
{
	wchar_t *str;

	str = (wchar_t *)print->data;
	if (fields->point && str == NULL)
		str = ft_wstrsub(L"(null)", 0, fields->precision);
	else if (str == NULL)
		str = ft_wstrdup(L"(null)");
	else if (fields->point && ft_wstrlen(str) > fields->precision)
	{
		print->free = 0;
		str = ft_wstrsub(str, 0, fields->precision);
	}
	else
		print->free = 0;
	print->data = str;
	ft_flags_s(print, fields);
	return (*print);
}

t_pf_prints	pf_cvt_s(t_pf_prints *print, t_pf_fields *fields)
{
	if (fields->type == 's' && !ft_strchr("lL", fields->size))
		return (ft_cvt_s_lwr(print, fields));
	else
		return (ft_cvt_s_upr(print, fields));
}
