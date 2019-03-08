/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lenint_base.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/12 21:30:25 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/12 21:30:30 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/maths.h"

/*
** Compte la longeur d'un int selon une base.
*/

int		ft_lenint_base(uintmax_t nb, int base)
{
	int ret;

	ret = 1;
	while ((nb /= base))
		ret++;
	return (ret);
}
