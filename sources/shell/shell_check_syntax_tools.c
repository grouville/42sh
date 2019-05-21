/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_check_syntax_tools.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/04 17:56:56 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 17:56:57 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** Par securité on doucle check les redis out
*/

int		check_synthax_stdout_to(t_output *redis)
{
	t_output *read;

	read = redis;
	while (read != NULL)
	{
		if (!read->to || ft_strcmp(read->to, "&") == 0 ||
			ft_strcmp(read->to, ">") == 0 || ft_strcmp(read->to, ">>") == 0)
			return (1);
		if (read->to == NULL)
			return (0);
		read = read->next;
	}
	return (0);
}
