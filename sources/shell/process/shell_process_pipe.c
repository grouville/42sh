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

void	shell_child_pipe(t_cmd *elem, t_shell *shell, int fd_pipe[2])
{
	int		exec;
	char 	*tmp;

	printf("-<child |%s|close fd=%d>\n", elem->args[0], fd_pipe[0]);
	close(fd_pipe[0]);
	if (elem->sep == SPL_PIPE)
	{
		ft_strdel(&elem->process.fd_stdout);
		tmp = ft_itoa(fd_pipe[1]);
		elem->process.fd_stdout = ft_strjoin("&", tmp);
		ft_strdel(&tmp);
		//dup2(fd_pipe[1], 1);
	}
	exec = shell_exec(elem, shell);
	if (exec == 1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	shell_father_pipe(t_cmd *elem, int fd_pipe[2])
{
	char *tmp;

	printf("-<father %s|close %d|>\n",elem->args[0], fd_pipe[1]);
	close(fd_pipe[1]);
	if (ft_atoi(elem->process.fd_stdin + 1) != 0)
	{
		printf("-<father de %s close |%s|>\n", elem->args[0], elem->process.fd_stdin);
		close(ft_atoi(elem->process.fd_stdin + 1));
	}
	if (elem->next_cmd)
	{
		ft_strdel(&elem->next_cmd->process.fd_stdin);
		tmp = ft_itoa(fd_pipe[0]);
		elem->next_cmd->process.fd_stdin = ft_strjoin("&", tmp);
		printf("-<child de %s met fdstdin fd=|%s| pour %s>\n", elem->args[0], elem->next_cmd->process.fd_stdin, elem->next_cmd->args[0]);
		ft_strdel(&tmp);
	}
	else
		close(fd_pipe[0]);
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

	//printf("-<|%s|>\n", (*elem)->process.fd_stdin);
	elem_no_pipe = 0;
	while (elem_no_pipe == 0)
	{
		if ((*elem)->sep != SPL_PIPE)
			elem_no_pipe = 1;
		pipe(fd_pipe);
		printf("-<|%d|%d|>\n", fd_pipe[0], fd_pipe[1]);
		if ((child = fork()) == 0)
			shell_child_pipe(*elem, shell, fd_pipe);
		else
			shell_father_pipe(*elem, fd_pipe);
		if (elem_no_pipe == 0)
			*elem = (*elem)->next_cmd;
		//close(fd_pipe[0]);
		//close(fd_pipe[1]);
	}
	waitpid(child, &status, 0);
	while (wait(NULL) > 0)
		;
	return (status);
}
