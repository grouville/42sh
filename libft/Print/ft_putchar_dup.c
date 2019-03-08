/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putchar_dup.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/03 17:19:51 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/03 17:19:53 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/print.h"

/*
** Duplique et print le caractere {c}
*/

int	ft_putchar_dup(char c, int i)
{
	while (i--)
		ft_putchar(c);
	return (1);
}
