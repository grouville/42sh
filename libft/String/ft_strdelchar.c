/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdelchar.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 20:02:42 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 20:02:43 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Delete le premier {c} dans {str} si trouvé
*/

void	ft_strdelchar(char **str, char c)
{
	int	jump;
	int	i;

	jump = 0;
	i = 0;
	while (*str && (*str)[i - jump])
	{
		if ((*str)[i] == c)
			jump = 1;
		(*str)[i] = (*str)[i + jump];
		i++;
	}
	if (jump)
		(*str)[i] = '\0';
}
