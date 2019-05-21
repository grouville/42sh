/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wait_job.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 22:47:52 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 20:08:49 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		mark_process_status_norm(pid_t pid, int status, t_job **job)
{
	t_cmd	*elem;

	elem = (*job)->cmds;
	while (elem)
	{
		if (elem->pid == pid)
		{
			elem->status = status;
			if (WIFSTOPPED(status))
			{
				if (WSTOPSIG(elem->status))
					(*job)->running = WSTOPSIG(elem->status);
				elem->stopped = 1;
			}
			else
			{
				elem->done = 1;
				if (WIFSIGNALED(status))
					elem->signal = WTERMSIG(elem->status);
			}
			return (0);
		}
		elem = elem->next_cmd;
	}
	return (1);
}

/*
*** - Store the status of the process pid that was returned by waitpid.
*** - Return 0 if all went well, nonzero otherwise.
*/

int		mark_process_status(pid_t pid, int status)
{
	t_job	*job;

	if (pid > 0)
	{
		job = getter_job()->first_job;
		while ((job = job->next))
		{
			if (!mark_process_status_norm(pid, status, &job))
				return (0);
		}
		return (-1);
	}
	else if (pid == 0)
		return (-1);
	else
		return (-1);
}

void	wait_for_job(t_job *j)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
		if (mark_process_status(pid, status))
			break ;
		if (job_is_stopped(j))
			break ;
		if (job_is_completed(j))
			break ;
	}
}
