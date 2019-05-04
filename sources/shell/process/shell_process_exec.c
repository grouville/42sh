/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_exec.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 22:44:23 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/21 22:44:23 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	shell_exec_print_error(t_cmd *elem)
{
	if (ft_strcmp("not found", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: command not found\n", elem->args[0]);
	else if (ft_strcmp("directory", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: Is a directory\n", elem->args[0]);
	else if (ft_strcmp("file or directory", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: No such file or directory\n",
				   elem->args[0]);
	else if (ft_strcmp("no allowed", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: Permission denied\n", elem->args[0]);
}

int		shell_exec_error(t_cmd *elem)
{
	int ret;

	ret = 1;
	if (elem->exec)
	{
		shell_exec_print_error(elem);
		if (ft_strcmp("no allowed", elem->exec) == 0 ||
			ft_strcmp("directory", elem->exec) == 0)
			exit(126);
		else if (ft_strcmp("file or directory", elem->exec) == 0 ||
				 ft_strcmp("not found", elem->exec) == 0)
			exit(127);
		else
			ret = 0;
	}
	return (ret);
}

void	shell_child(t_cmd *elem, t_shell *shell, t_job *job)
{
	pid_t	pid;
	t_js	*jsig;
	int 	builtin;

	jsig = getter_job();
	if (jsig->shell_is_interactive)
	{
		/* Put the process into the process group and give the process group
		   the terminal, if appropriate.
		   This has to be done both by the shell and in the individual
		   child processes because of potential race conditions.  */
		pid = getpid ();
		setpgid (pid, (job->pgid == 0) ? pid : job->pgid);
		if (job->sep != SPL_SPRLU)
			tcsetpgrp (jsig->shell_terminal, (job->pgid == 0) ? pid : job->pgid);

		/* Set the handling for job control signals back to the default.  */
		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		signal (SIGTSTP, SIG_DFL);
		signal (SIGTTIN, SIG_DFL);
		signal (SIGTTOU, SIG_DFL);
		signal (SIGCHLD, SIG_DFL);
	}
	if (elem->bad_substitution)
		exit(EXIT_FAILURE);
	if (!shell_read_input(elem, shell) || !shell_set_output(elem, shell))
		exit(EXIT_FAILURE);
	//read_lexing(elem);
	shell_plomberie(elem->process);
	if (!(builtin = shell_builtin(elem, shell)) && !shell_exec_error(elem))
		execve(elem->exec, elem->args, shell->envp);
	exit(EXIT_SUCCESS);
}

int		shell_father(int pid_child, t_cmd *elem)
{
	int status;

	status = -4735;
	if (elem->sep != SPL_SPRLU)
		waitpid(pid_child, &status, WUNTRACED); //WUNTRACED pour le Ctrl-Z
	return (status);
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
		elem->ret = shell_father(child, elem);
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
		setpgid (child, job->pgid);
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
			(is_builtin = shell_is_builtin(elem, shell)))
	{
		if (!shell_read_input(elem, shell) || !shell_set_output(elem, shell))
			return (1);
		//read_lexing(elem);
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
