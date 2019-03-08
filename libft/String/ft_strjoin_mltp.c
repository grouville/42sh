/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoins.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/28 13:57:47 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/28 13:57:49 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

char	*ft_strjoin_mltp(int n, ...)
{
	va_list	ap;
	char	*tmp;
	char	*cpy;
	char	*ret;

	ret = ft_strdup("");
	va_start(ap, n);
	while (n--)
	{
		tmp = va_arg(ap, char *);
		if (!tmp)
			break ;
		cpy = ret;
		ret = ft_strjoin(cpy, tmp);
		free(cpy);
	}
	va_end(ap);
	return (ret);
}
