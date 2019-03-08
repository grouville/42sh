/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_clean.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/23 20:20:21 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/23 20:20:21 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Include/shell.h"

void	clean_arr_mlti(char **arr)
{
	int i;

	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		if ((int)arr[i] == -1 || (int)arr[i] == -2 || (int)arr[i] == -3)
			arr[i++] = NULL;
		else
			ft_strdel(&arr[i++]);
	}
	if (arr != NULL)
		free(arr);
}

void	clean_redi(t_output **redi)
{
	t_output	*tmp;

	while ((*redi)->next != NULL)
	{
		tmp = *redi;
		(*redi) = (*redi)->next;
		ft_strdel(&tmp->to);
		free(tmp);
	}
	ft_strdel(&(*redi)->to);
	free(*redi);
}

void	clean_cmd(t_cmd **cmd)
{
	t_cmd	*prev;

	if (*cmd)
	{
		*cmd = (*cmd)->start;
		prev = *cmd;
		while ((*cmd = (*cmd)->next_cmd))
		{
			ft_arrdel(&(*cmd)->args);
			clean_arr_mlti((*cmd)->hrdc);
			clean_arr_mlti((*cmd)->input);
			ft_strdel(&(*cmd)->process.fd_stdin);
			ft_strdel(&(*cmd)->process.fd_stdout);
			ft_strdel(&(*cmd)->process.fd_stderr);
			if ((int)(*cmd)->process.stdin_send != -1)
				ft_strdel(&(*cmd)->process.stdin_send);
			ft_strdel(&(*cmd)->exec);
			if ((*cmd)->output)
				clean_redi(&((*cmd)->output));
			free(prev);
			prev = *cmd;
		}
		free(prev);
		*cmd = NULL;
	}
}

int		shell_clean_data(t_cmd **cmd, t_shell *shell, BOOL hrdc_tmp)
{
	clean_cmd(cmd);
	ft_strdel(&shell->str);
	if (hrdc_tmp)
		ft_strdel(&shell->hrdc_tmp);
	return (1);
}
