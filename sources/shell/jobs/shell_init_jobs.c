/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_init_jobs.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 14:38:59 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 14:38:59 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
*** - Aim of the function :
*** - Make sure the shell is running interactively as the foreground job
*** - before proceeding
*/

void        init_shell_job(t_shell *shell)
{
	pid_t   shell_pgid;

	// Check if we are running interactively
	shell->is_interactive = isatty(STDIN_FILENO);
	if (shell->is_interactive)
	{
		// Loop until we are in the foreground
		while (tcgetpgrp(STDIN_FILENO) != (shell_pgid = getpgrp()))
			kill(shell_pgid, SIGTTIN);

		// Ignore interactive and job-control signals
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, SIG_IGN);

		// Put ourselves in our own process group
		shell_pgid = getpid();
		if (setpgid(shell_pgid, shell_pgid) < 0)
		{
			ft_dprintf(1,
					   "Bash : Couldn't put the shell in its own process group\n");
			free(shell);
			exit(1);
		}
		// Grab control of the terminal
		tcsetpgrp(STDIN_FILENO, shell_pgid);
	}
}
