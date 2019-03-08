/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fields.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/15 14:16:25 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/15 14:16:25 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

t_pf_fields	pf_fields_reset(void)
{
	t_pf_fields fields;

	fields.diese = 0;
	fields.zero = 0;
	fields.moins = 0;
	fields.plus = 0;
	fields.space = 0;
	fields.point = 0;
	fields.size = 0;
	fields.width = 0;
	fields.precision = 0;
	fields.type = 0;
	fields.wldcrd_width = 0;
	fields.wldcrd_prec = 0;
	return (fields);
}

t_pf_prints	pf_print_reset(void)
{
	t_pf_prints print;

	print.data = 0;
	print.space_bfr = 0;
	print.space_aftr = 0;
	print.zero_bfr = 0;
	print.zero_aftr = 0;
	print.plus = 0;
	print.minus = 0;
	print.space = 0;
	print.zero_x = 0;
	print.zero_x_up = 0;
	print.free = 1;
	return (print);
}
