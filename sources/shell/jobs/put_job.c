/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   put_job.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 23:01:39 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 19:02:37 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
*** - Aim of the function :
*** - wait only used when fg and bg are being processed
*/

void	wait_for_job_fg_bg(t_job *j)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (mark_process_status(pid, status))
			break ;
		if (job_is_stopped(j))
			break ;
		if (job_is_completed(j))
			break ;
	}
}

/*
*** - Put job j in the foreground.  If cont is nonzero,
*** - restore the saved terminal modes and send the process group a
*** - SIGCONT signal to wake it up before we block.
*/

void	put_job_in_foreground(t_job *j, int cont)
{
	t_js	*jsig;

	jsig = getter_job();
	tcsetpgrp(jsig->shell_terminal, j->pgid);
	if (!shell_nothere(j))
		put_job_done(j);
	if (cont)
	{
		if (j->running && j->running != 999)
		{
			tcsetattr(jsig->shell_terminal, TCSADRAIN, &j->tmodes);
			if (kill(-j->pgid, SIGCONT) < 0)
				;
		}
		wait_for_job_fg_bg(j);
	}
	else
		wait_for_job(j);
	tcsetpgrp(jsig->shell_terminal, jsig->shell_pgid);
	tcgetattr(jsig->shell_terminal, &j->tmodes);
	tcsetattr(jsig->shell_terminal, TCSADRAIN, &(jsig->shell_tmodes));
}

/*
*** - Put a job in the background.  If the cont argument is true, send
*** - the process group a SIGCONT signal to wake it up.
*/

void	put_job_in_background(t_job *j, int cont)
{
	ft_dprintf(1, "[%d] %d\n", j->num, j->pgid);
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			;
}

void	put_process_suspended(t_job *j, t_cmd *elem)
{
	t_js	*jsig;

	j->sep = SPL_SPRLU;
	j->running = 1;
	elem->stopped = 1;
	j->notified_crtrz = 1;
	ft_dprintf(1, "[%d]+  %-10s%s\n", j->num, "Stopped", elem->args[0]);
	jsig = getter_job();
	tcsetpgrp(jsig->shell_terminal, jsig->shell_pgid);
	tcgetattr(jsig->shell_terminal, &j->tmodes);
	tcsetattr(jsig->shell_terminal, TCSADRAIN, &(jsig->shell_tmodes));
}
