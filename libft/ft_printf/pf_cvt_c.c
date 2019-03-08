/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_cvt_c.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/17 14:19:57 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/17 14:19:57 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/ft_printf.h"

t_pf_prints	*ft_flags_c(t_pf_prints *print, t_pf_fields *fields)
{
	if (!(fields->moins))
	{
		if (fields->zero)
			print->zero_bfr = fields->width - 1;
		else
			print->space_bfr = fields->width - 1;
	}
	if (fields->moins)
	{
		if (fields->zero)
			print->zero_aftr = fields->width - 1;
		else
			print->space_aftr = fields->width - 1;
	}
	return (print);
}

t_pf_prints	pf_cvt_c(t_pf_prints *print, t_pf_fields *fields)
{
	wchar_t *c;

	c = (wchar_t *)print->data;
	ft_flags_c(print, fields);
	if (ft_strchr("lL", fields->size))
		fields->type = 'C';
	print->data = (void *)c;
	return (*print);
}
