/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wait_job.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 22:47:52 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 22:47:52 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/* Store the status of the process pid that was returned by waitpid.
   Return 0 if all went well, nonzero otherwise.  */

int mark_process_status (pid_t pid, int status)
{
	t_job *job;
	t_cmd *elem;

	int i = 0;
	if (pid > 0)
	{
		/* Update the record for the process.  */
		job = first_job;
		while ((job = job->next))
		{
		//for (job = first_job; job; job = job->next)
		//{
			for (elem = job->cmds; elem; elem = elem->next_cmd)
			{
				if (elem->pid == pid)
				{
					elem->status = status;
					if (WIFSTOPPED (status))
						elem->stopped = 1;
					else
					{
						elem->completed = 1;
						if (WIFSIGNALED (status))
							fprintf(stderr, "%d: Terminated by signal %d.\n",
									(int) pid, WTERMSIG (elem->status));
					}
					{
						printf("-<|return 0|>\n");
						return 0;
					}
				}
				fprintf(stderr, "process %d et %d\n", pid, elem->pid);
			}
			printf("-<|boucle %d|>\n", i++);
		}
		fprintf (stderr, "No child process %d et %d\n", pid, elem->pid);
		return -1;
	}

	else if (pid == 0)
		/* No processes ready to report.  */
	{
		printf("-<|pid == 0 OU possibilité de errno == ECHILD|>\n");
		return -1;
	}
	else {
		/* Other weird errors.  */
		printf("-<|werid error|>\n");
		perror ("waitpid");
		return -1;
	}
}


void wait_for_job (t_job *j)
{
	int status;
	pid_t pid;

	do
		pid = waitpid (WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status (pid, status)
		   && !job_is_stopped (j)
		   && !job_is_completed (j));
}
