/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_split.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/30 21:18:39 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/30 21:18:39 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		get_sep(char **str)
{
	int		sep;

	*str = shell_trim(str);
	sep = 0;
	sep = (*str)[0] == '|' ? SPL_PIPE : sep;
	sep = (*str)[0] == ';' ? PTN_VRGL : sep;
	sep = (*str)[0] == '&' ? SPL_SPRLU : sep;
	sep = (*str)[0] == '|' && (*str)[1] == '|' ? DBL_PIPE : sep;
	sep = (*str)[0] == '&' && (*str)[1] == '&' ? DBL_SPRLU : sep;
	if ((sep >= 1 && sep <= 2) || sep == 5)
		*str = *str + 1;
	else if (sep >= 3)
		*str = *str + 2;
	return (sep);
}

BOOL	stdout_to(t_output *redis)
{
	t_output	*read;

	read = redis;
	while (read != NULL)
	{
		if (read->to == NULL)
			return (0);
		read = read->next;
	}
	return (1);
}

BOOL	ft_isempty(char *str)
{
	int i;

	i = 0;
	while (str && ft_isspace(str[i]))
		i++;
	if (str && i == ft_strlen(str))
		return (1);
	else
		return (0);
}

/*
** split line jusqu'au prochain delimiteur
** Le premier maillon start de {cmd} (pointé par tous les autres) est vide.
*/

t_cmd	*shell_split(char *line, char **envp, t_prompt *prompt)
{
	t_cmd	*cmd;

	if (ft_isempty(line) || !iscomplet(line, prompt))
		return (NULL);
	cmd = (t_cmd *)shl_mlc("cmd", 3, &line, envp, sizeof(t_cmd));
	cmd->start = cmd;
	while (line && (cmd->next_cmd = get_args(&line, envp, prompt)))
	{
		(cmd->next_cmd)->start = cmd->start;
		cmd = cmd->next_cmd;
		cmd->sep = get_sep(&line);
		if (!stdout_to(cmd->output))
			break ;
	}
	if (!cmd->args || (ft_strlen(*cmd->args) && (cmd->sep == SPL_PIPE ||
			cmd->sep == DBL_PIPE || cmd->sep == DBL_SPRLU)))
	{
		*prompt = B_QUOTE;
		clean_cmd(&cmd);
		return (NULL);
	}
	else
		*prompt = PROMPT;
	return (cmd->start);
}
