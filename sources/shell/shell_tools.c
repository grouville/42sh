/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/18 15:24:03 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/18 15:24:03 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

char	*get_next_hrdc(char **hrdc)
{
	int	i;

	i = 0;
	while (hrdc && (int)hrdc[i] == -3)
		i++;
	return (hrdc ? hrdc[i] : NULL);
}

void	shl_quotesub(char *arg)
{
	char	quote;

	quote = ft_strchr("'\"", *arg) ? *arg : (char)' ';
	if (quote != ' ')
		ft_strdelchar(&arg, quote);
	while (*arg)
	{
		if (*arg == '\\' && quote != '\'')
		{
			ft_strdelchar(&arg, *arg);
			arg++;
		}
		else if (ft_strchr("'\"", *arg) && quote == ' ')
			ft_strdelchar(&arg, quote = *arg);
		else if (*arg == quote && quote != ' ')
		{
			ft_strdelchar(&arg, quote);
			quote = ' ';
		}
		else
			arg++;
	}
}

void	clean_shell(t_shell **shell)
{
	ft_arrdel(&(*shell)->envp);
	ft_arrdel(&(*shell)->envl);
	ft_arrdel(&(*shell)->alias);
	ft_strdel(&(*shell)->str);
	ft_strdel(&(*shell)->hrdc_tmp);
	ft_strdel(&(*shell)->hist_path);
	free(*shell);
	*shell = NULL;
}

void	shell_save_fd(int fd[3])
{
	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[2] = dup(2);
}

void	shell_reinit_fd(int fd[3])
{
	int tmp_fd;

	tmp_fd = fd[0];
	dup2(fd[0], 0);
	close(tmp_fd);
	tmp_fd = fd[1];
	dup2(fd[1], 1);
	close(tmp_fd);
	tmp_fd = fd[2];
	dup2(fd[2], 2);
	close(tmp_fd);
}
