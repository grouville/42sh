/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   strsplit_mnshl2.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 20:27:35 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/29 20:27:35 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

char	*shell_trim(char **str)
{
	int i;

	i = 0;
	while (*str && ft_isspace((*str)[i]))
		i++;
	*str = *str + i;
	return (*str);
}

/*
** Return NULL si redi est dans le prochain arg (si existant) ou si quote
** non fermé.
*/

char	*get_stdout_to(char *redi, int pos)
{
	char	*redi_to;
	int		len;

	if (redi[pos] == '\0')
		return (NULL);
	len = len_stdout_to(redi + pos);
	if (len > 0)
		redi_to = ft_strsub(redi, (unsigned)pos, (size_t)len);
	else
		redi_to = NULL;
	return (redi_to);
}

BOOL	triple_chevrons(char *str)
{
	if (str[0] == '<' && str[1] == '<' && str[2] == '<')
		return (1);
	else
		return (0);
}