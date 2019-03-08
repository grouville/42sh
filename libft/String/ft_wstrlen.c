/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrlen.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/14 00:55:32 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/14 00:55:34 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

int	ft_wstrlen(const wchar_t *wstr)
{
	int cur;
	int ret;

	ret = 0;
	cur = 0;
	while (wstr[cur])
		ret += ft_size_wchar(wstr[cur++]);
	return (ret);
}
