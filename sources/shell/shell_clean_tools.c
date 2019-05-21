/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_clean_tools.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/04 18:00:08 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 18:00:10 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	clean_cmd2(t_cmd **cmd)
{
	ft_arrdel(&(*cmd)->args);
	ft_arrdel(&(*cmd)->args_raw);
	ft_arrdel(&(*cmd)->envl_exec);
	clean_arr_mlti((*cmd)->hrdc);
	clean_arr_mlti((*cmd)->input);
	ft_strdel(&(*cmd)->process.fd_stdin);
	ft_strdel(&(*cmd)->process.fd_stdout);
	ft_strdel(&(*cmd)->process.fd_stderr);
}

void	clean_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (cmd && *cmd)
	{
		while ((*cmd))
		{
			clean_cmd2(cmd);
			if ((int)(*cmd)->process.stdin_send != -1 &&
				(int)(*cmd)->process.stdin_send != -2)
				ft_strdel(&(*cmd)->process.stdin_send);
			ft_strdel(&(*cmd)->exec);
			if ((*cmd)->output)
				clean_redi(&((*cmd)->output));
			if (!(tmp = (*cmd)->next_cmd))
			{
				free(*cmd);
				return ;
			}
			free(*cmd);
			*cmd = tmp;
		}
		*cmd = NULL;
	}
}
