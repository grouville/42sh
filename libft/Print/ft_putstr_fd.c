/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:28:00 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/20 05:07:43 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "print.h"

int		ft_putstr_fd(char const *s, int fd)
{
	unsigned int i;

	if (s)
	{
		i = ft_strlen(s);
		write(fd, s, i);
		return (i);
	}
	return (0);
}
