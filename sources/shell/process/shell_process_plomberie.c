/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_plomberie.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/13 17:46:13 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 17:46:13 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** On envoi send_stdin dans le tuyau temporaire tmp_fd.
** On le ferme pour envoyer EOF
*/

void	shell_pipe_stdin(char *send_stdin)
{
	int tmp_fd[2];

	pipe(tmp_fd);
	ft_putstr_fd(send_stdin, tmp_fd[1]);
	close(tmp_fd[1]);
	dup2(tmp_fd[0], 0);
	close(tmp_fd[0]);
}

void	shell_pipe_stdout(t_process process)
{
	if (process.fd_stdout[0] == '&' && process.fd_stdout[1] != '1')
		dup2(ft_atoi(process.fd_stdout + 1), 1);
	else if (process.fd_fileout != 0)
		dup2(process.fd_fileout, 1);
}

void	shell_pipe_stderr(t_process process)
{
	if (process.fd_stderr[0] == '&' && process.fd_stderr[1] != '2')
		dup2(ft_atoi(process.fd_stderr + 1), 2);
	else if (process.fd_fileerr != 0)
		dup2(process.fd_fileerr, 2);
}

/*
** Les redirections stdout sont prio sur le pipe
** La dernière redirection se dup2 en dernière
*/

void	shell_plomberie(t_process process)
{
	if (process.stdin_send)
		shell_pipe_stdin(process.stdin_send);
	if (process.last_redi == 1)
	{
		shell_pipe_stderr(process);
		shell_pipe_stdout(process);
	}
	else
	{
		shell_pipe_stdout(process);
		shell_pipe_stderr(process);
	}
}
