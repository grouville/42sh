/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_check.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 00:43:10 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/16 11:03:37 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

BOOL	shell_hrdc_quotesub(t_cmd *cmd, t_shell *shell, t_prompt *prompt)
{
	int i;

	ft_strjoin_free(&shell->hrdc_tmp, shell->str);
	ft_strjoin_free(&shell->hrdc_tmp, "\n");
	ft_strdel(&shell->str);
	*prompt = HRDC;
	i = 0;
	while (cmd->hrdc[i] != NULL)
		shl_quotesub(cmd->hrdc[i++]);
	return (1);
}

BOOL	cmd_check(t_cmd **cmd, t_shell *shell, t_prompt *prompt)
{
	t_cmd	*next;

	*cmd = (*cmd)->start;
	next = *cmd;
	while ((next = next->next_cmd))
	{
		if (next->hrdc && ((int)next->hrdc[0] < -3 || (int)next->hrdc[0] > -1))
			return (shell_hrdc_quotesub((*cmd = next), shell, prompt));
	}
	return (0);
}
