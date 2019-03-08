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

#include "../../../Include/shell.h"

/*
** shell exec peut retourner 0=RAS ou -1=quite mais pas dans un pipe
*/

void	shell_child_pipe(t_cmd *elem, t_shell *shell, int fd_pipe[2])
{
	int		exec;

	dup2(ft_atoi(elem->process.fd_stdin + 1), 0);
	if (elem->sep == SPL_PIPE)
		dup2(fd_pipe[1], 1);
	close(fd_pipe[0]);
	exec = shell_exec(elem, shell);
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
}

/*
** On fait un waitpid pour save status qu'on return
*/

int		shell_exec_pipes(t_cmd **elem, t_shell *shell)
{
	int		fd_pipe[2];
	int		child;
	BOOL	elem_no_pipe;
	int		status;

	elem_no_pipe = 0;
	while (elem_no_pipe == 0)
	{
		if ((*elem)->sep != SPL_PIPE)
			elem_no_pipe = 1;
		pipe(fd_pipe);
		if ((child = fork()) == 0)
			shell_child_pipe(*elem, shell, fd_pipe);
		else
			shell_father_pipe(*elem, fd_pipe);
		if (elem_no_pipe == 0)
			*elem = (*elem)->next_cmd;
	}
	waitpid(child, &status, 0);
	while (wait(NULL) > 0)
		;
	return (status);
}
