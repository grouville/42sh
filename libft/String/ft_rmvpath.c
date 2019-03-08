/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_rmvpath.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/24 02:24:03 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/24 02:39:54 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** ft_rmvpath : le while prend un compte le dernier '/' en fin de path
** et le conserve. Ex ~/path/de/mon/fichier/ --> fichier/
*/

char	*ft_rmvpath(char *str)
{
	if (!ft_strchr(str, '/') && (ft_strchr(str, '/') + 1) == '\0')
		return (str);
	else
	{
		while (ft_strchr(str, '/') != 0 && ft_strlen(ft_strchr(str, '/')) != 1)
			str = ft_strchr(str, '/') + 1;
		return (str);
	}
}
