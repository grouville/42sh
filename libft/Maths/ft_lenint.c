/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lenint.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:26:24 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:26:24 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/maths.h"

/*
** Retoune la longeur d'un int. Le signe - est compté comme un chiffre.
*/

int		ft_lenint(int n)
{
	int	ret;

	ret = 1;
	if (n < 0)
		ret++;
	while ((n /= 10))
		ret++;
	return (ret);
}
