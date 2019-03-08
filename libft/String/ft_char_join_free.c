/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_char_join_free.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/01 23:16:32 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 23:16:32 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/string.h"

void	ft_char_join_free(char c, char **str)
{
	char tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	ft_strjoin_free(str, tmp);
}
