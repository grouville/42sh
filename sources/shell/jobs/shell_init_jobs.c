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

void handle(int sig)
{
	(void)sig;
}

/* Make sure the shell is running interactively as the foreground job
   before proceeding. */

void process_init_shell_for_job(void)
{
	t_js	*jsig;

	jsig = getter_job();
	/* See if we are running interactively.  */
	jsig->shell_terminal = STDIN_FILENO;
	jsig->shell_is_interactive = isatty (jsig->shell_terminal);

	if (jsig->shell_is_interactive)
	{
		/* Loop until we are in the foreground.  */
		while (tcgetpgrp (jsig->shell_terminal) != (jsig->shell_pgid = getpgrp ()))
			kill (- jsig->shell_pgid, SIGTTIN);

		/* Ignore interactive and job-control signals.  */
		signal (SIGINT, SIG_IGN);
		signal (SIGQUIT, SIG_IGN);
		signal (SIGTSTP, SIG_IGN);
		signal (SIGTTIN, SIG_IGN);
		signal (SIGTTOU, SIG_IGN);
		signal (SIGCHLD, handle);

		/* Put ourselves in our own process group.  */
		jsig->shell_pgid = getpid ();
		if (setpgid (jsig->shell_pgid, jsig->shell_pgid) < 0)
		{
			ft_dprintf(2, "Couldn't put the shell in its own process group");
			exit (1);
		}

		/* Grab control of the terminal.  */
		tcsetpgrp (jsig->shell_terminal, jsig->shell_pgid);

		/* Save default terminal attributes for shell.  */
		tcgetattr (jsig->shell_terminal, &(jsig->shell_tmodes));
	}
}
