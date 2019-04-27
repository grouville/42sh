/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_pipe.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/17 17:54:45 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/17 17:54:45 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** shell exec peut retourner 0=RAS ou -1=quite mais pas dans un pipe
*/

void	shell_child_pipe(t_cmd *elem, t_shell *shell, int fd_pipe[2], t_job *job)
{
	int		exec;
	char 	*tmp;

	close(fd_pipe[0]);
	if (elem->sep == SPL_PIPE)
	{
		ft_strdel(&elem->process.fd_stdout);
		tmp = ft_itoa(fd_pipe[1]);
		elem->process.fd_stdout = ft_strjoin("&", tmp);
		ft_strdel(&tmp);
	}
	exec = shell_exec(elem, shell, job);
	if (exec == 1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	shell_father_pipe(t_cmd *elem, int fd_pipe[2])
{
	char *tmp;

	close(fd_pipe[1]);
	if (ft_atoi(elem->process.fd_stdin + 1) != 0)
		close(ft_atoi(elem->process.fd_stdin + 1));
	if (elem->next_cmd)
	{
		ft_strdel(&elem->next_cmd->process.fd_stdin);
		tmp = ft_itoa(fd_pipe[0]);
		elem->next_cmd->process.fd_stdin = ft_strjoin("&", tmp);
		ft_strdel(&tmp);
	}
	else
		close(fd_pipe[0]);
}

/*
** On fait un waitpid pour save status qu'on return
*/

int		shell_exec_pipes(t_cmd **elem, t_shell *shell, t_job *job)
{
	int		fd_pipe[2];
	int		child;
	BOOL	elem_no_pipe;
	int		status;
	int 	status2;

	elem_no_pipe = 0;
	while (elem_no_pipe == 0)
	{
		if ((*elem)->sep != SPL_PIPE)
			elem_no_pipe = 1;
		pipe(fd_pipe);
		if ((child = fork()) == 0)
			shell_child_pipe(*elem, shell, fd_pipe, job);
		else
			shell_father_pipe(*elem, fd_pipe);
		if (elem_no_pipe == 0)
			*elem = (*elem)->next_cmd;
		if (!shell_prepare_args(*elem, shell))
			return(0);
	}
	waitpid(child, &status, 0);
	while (waitpid(0, &status2, WUNTRACED) > 0)
		;
	return (status);
}
