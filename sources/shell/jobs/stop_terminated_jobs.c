/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stop_terminated_jobs.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 18:25:51 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/18 18:25:51 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "shell.h"


/* Check for processes that have status information available,
   without blocking.  */

void update_status (void)
{
	int status;
	pid_t pid;

	do
		pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!mark_process_status (pid, status));
}


/* Format information about job status for the user to look at.  */

void format_job_info (t_job *j, const char *status)
{
	fprintf (stderr, "%ld (%s): %s\n", (long)j->pgid, status, j->command);
}


/* Notify the user about stopped or terminated jobs.
   Delete terminated jobs from the active job list.  */

void do_job_notification (void)
{
	t_job *j, *jlast, *jnext;
	t_cmd *p;

	/* Update status information for child processes.  */
	update_status ();

	jlast = NULL;
	j = first_job;
	while ((j = j->next))
	{
		jnext = j->next;

		/* If all processes have completed, tell the user the job has
		   completed and delete it from the list of active jobs.  */
		if (job_is_completed (j)) {
			format_job_info (j, "completed");
			if (jlast)
				jlast->next = jnext;
			else
				first_job = jnext;
			//free_job (j);
		}

			/* Notify the user about stopped jobs,
			   marking them so that we won’t do this more than once.  */
		else if (job_is_stopped (j) && !j->notified) {
			format_job_info (j, "stopped");
			j->notified = 1;
			jlast = j;
		}

			/* Don’t say anything about jobs that are still running.  */
		else
			jlast = j;
	}
}
