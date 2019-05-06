/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_exec.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 22:44:23 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:30:22 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	shell_child(t_cmd *elem, t_shell *shell, t_job *job)
{
	pid_t	pid;
	t_js	*jsig;

	jsig = getter_job();
	if (jsig->shell_is_interactive)
	{
		pid = getpid();
		setpgid(pid, (job->pgid == 0) ? pid : job->pgid);
		if (job->sep != SPL_SPRLU)
			tcsetpgrp(jsig->shell_terminal, (job->pgid == 0) ? pid : job->pgid);
		child_signals_to_dfl();
	}
	if (elem->bad_substitution)
		exit(EXIT_FAILURE);
	if (!shell_read_input(elem, shell) || !shell_set_output(elem, shell))
		exit(EXIT_FAILURE);
	if (elem->envl_exec)
		shell_add_envl_exec(elem->envl_exec, shell);
	shell_plomberie(elem->process);
	if (shell_is_builtin(elem))
		shell_builtin(elem, shell);
	else if (!shell_exec_error(elem))
		execve(elem->exec, elem->args, shell->envp);
	exit(EXIT_SUCCESS);
}

int		right_return(int status)
{
	int res;

	res = 0;
	if (WIFEXITED(status))
		res = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		res = manage_sig_term_ret(WTERMSIG(status));
	else if (status == 4735)
		return (4735);
	return (res);
}

int		shell_father(int pid_child, t_cmd *elem, t_job *job)
{
	int status;
	int ret;

	ret = -4735;
	if (job->sep != SPL_SPRLU)
	{
		waitpid(pid_child, &status, WUNTRACED);
		if (elem->sep != SPL_PIPE)
			ret = right_return(status);
	}
	return (ret);
}

/*
** On retourne 0 si EXIT_SUCCESS ou 1 si EXIT_FAILED
** elem->ret == -/+ 4735 lorsque le process est en background
*/

int		shell_execve(t_cmd *elem, t_shell *shell, t_job *job)
{
	int		child;
	t_js	*jsig;

	if ((child = fork()) == 0)
		shell_child(elem, shell, job);
	else
		elem->ret = shell_father(child, elem, job);
	if (elem->ret == 4735 || job->sep == SPL_SPRLU)
	{
		elem->stopped = 1;
		elem->done = 0;
		job->running = 999;
	}
	if (elem->ret == 3)
		ft_dprintf(2, "Quit : 3\n");
	jsig = getter_job();
	elem->pid = child;
	if (jsig->shell_is_interactive)
	{
		if ((job->sep == SPL_SPRLU || elem->ret == 4735) && !job->pgid)
			job->pgid = child;
		setpgid(child, job->pgid);
	}
	return (elem->ret);
}

/*
** ATTENTION : shell_exec est dans un fork donc ne pas modif envp & envl
** return :
**   0 --> ok elem suivant
**   1 --> elem fail
**  -1 --> un exit est nécessaire
**
** Dans le cas d'un builtin on ne fork pas cependant les signaux sont SIG_IGN
** donc pas de Ctrl-C/D/Z et open d'un fifo bloquant
*/

int		shell_exec(t_cmd *elem, t_shell *shell, t_job *job)
{
	int	is_builtin;

	is_builtin = 0;
	if (job->sep != SPL_SPRLU && !elem->bad_substitution &&
			(is_builtin = shell_is_builtin(elem)))
	{
		if (!shell_read_input(elem, shell) || !shell_set_output(elem, shell))
			return (1);
		shell_plomberie(elem->process);
		if (shell_builtin(elem, shell) == -1)
			return (-1);
	}
	else if (!is_builtin && elem->exec && !elem->bad_substitution)
		elem->ret = shell_execve(elem, shell, job);
	if (elem->process.fd_stdin[1] != '0')
		close(ft_atoi(elem->process.fd_stdin + 1));
	if (elem->process.fd_fileout != 1)
		close(elem->process.fd_fileout);
	if (elem->process.fd_fileerr != 2)
		close(elem->process.fd_fileerr);
	return (elem->ret);
}
