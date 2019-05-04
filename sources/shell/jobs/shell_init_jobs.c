/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_init_jobs.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 14:38:59 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 19:11:29 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	handle(int sig)
{
	(void)sig;
}

/*
*** - Make sure the shell is running interactively as the foreground job
*** - before proceeding.
*/

void	process_init_shell_for_job(void)
{
	t_js	*jsig;

	jsig = getter_job();
	jsig->shell_terminal = STDIN_FILENO;
	jsig->shell_is_interactive = isatty(jsig->shell_terminal);
	if (jsig->shell_is_interactive)
	{
		while (tcgetpgrp(jsig->shell_terminal)
				!= (jsig->shell_pgid = getpgrp()))
			kill(-jsig->shell_pgid, SIGTTIN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, handle);
		jsig->shell_pgid = getpid();
		if (setpgid(jsig->shell_pgid, jsig->shell_pgid) < 0)
		{
			ft_dprintf(2, "Couldn't put the shell in its own process group");
			exit(1);
		}
		tcsetpgrp(jsig->shell_terminal, jsig->shell_pgid);
		tcgetattr(jsig->shell_terminal, &(jsig->shell_tmodes));
	}
}
