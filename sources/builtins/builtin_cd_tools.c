/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd_tools.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/08 13:19:17 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/08 13:19:17 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Include/shell.h"

/*
** se poisitonne au dernier '/' et remet a '\0' jusqu'a la fin
** sauf si on est a la racine
*/

char	*cd_rmv_last_path(char *cur_dir)
{
	char *tmp;

	if (ft_strlen(cur_dir) > 1)
	{
		tmp = ft_strchr(cur_dir, '/') + 1;
		while (ft_strchr(tmp, '/'))
			tmp = ft_strchr(tmp, '/') + 1;
		while (*tmp)
			*tmp++ = '\0';
	}
	return (cur_dir);
}
