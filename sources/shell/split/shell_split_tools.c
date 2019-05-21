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

void	is_complet_read_str(char *str, char *ptn_quote, int *ptn_i)
{
	*ptn_i = 0;
	*ptn_quote = ' ';
	while (str && str[*ptn_i])
	{
		if (str[*ptn_i] == '\\' && ft_strlen(str) >= (*ptn_i + 2) &&
				*ptn_quote != '\'')
			*ptn_i += 1;
		else if (ft_strchr("'\"", str[*ptn_i]) && *ptn_quote == ' ')
			*ptn_quote = str[*ptn_i];
		else if (str[*ptn_i] == '$' && str[*ptn_i + 1] == '{' &&
					*ptn_quote == ' ')
			*ptn_quote = '}';
		else if (str[*ptn_i] == *ptn_quote && *ptn_quote != ' ')
			*ptn_quote = ' ';
		*ptn_i += (str[*ptn_i] ? 1 : 0);
	}
}

/*
** Verifie si les quotes sont fermées et {\} en fin non présent
*/

BOOL	iscomplet(char *str, t_prompt *prompt)
{
	int		i;
	char	quote;

	i = 0;
	quote = ' ';
	is_complet_read_str(str, &quote, &i);
	if ((i > 0 && quote != ' ') || (i == 1 && str[0] == '\\'))
	{
		if (quote == '"')
			*prompt = D_QUOTE;
		else if (quote == '\'')
			*prompt = S_QUOTE;
		else if (quote == '}')
			*prompt = BRACE;
		return (0);
	}
	else if (str && (i > 0 && str[i - 1] == '\\' && chbkote(str + i, str)))
	{
		*prompt = BACKSLASH;
		return (0);
	}
	else
		return (1);
}

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
