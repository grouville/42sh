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

	/* See if we are running interactively.  */
	g_jsig.shell_terminal = STDIN_FILENO;
	g_jsig.shell_is_interactive = isatty (g_jsig.shell_terminal);

	if (g_jsig.shell_is_interactive)
	{
		/* Loop until we are in the foreground.  */
		while (tcgetpgrp (g_jsig.shell_terminal) != (g_jsig.shell_pgid = getpgrp ()))
			kill (- g_jsig.shell_pgid, SIGTTIN);

		/* Ignore interactive and job-control signals.  */
		signal (SIGINT, SIG_IGN);
		signal (SIGQUIT, SIG_IGN);
		signal (SIGTSTP, SIG_IGN);
		signal (SIGTTIN, SIG_IGN);
		signal (SIGTTOU, SIG_IGN);
		signal (SIGCHLD, handle);

		/* Put ourselves in our own process group.  */
		g_jsig.shell_pgid = getpid ();
		if (setpgid (g_jsig.shell_pgid, g_jsig.shell_pgid) < 0)
		{
			ft_dprintf(2, "Couldn't put the shell in its own process group");
			exit (1);
		}

		/* Grab control of the terminal.  */
		tcsetpgrp (g_jsig.shell_terminal, g_jsig.shell_pgid);

		/* Save default terminal attributes for shell.  */
		tcgetattr (g_jsig.shell_terminal, &(g_jsig.shell_tmodes));
	}
}
