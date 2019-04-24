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
	t_js	*jsig;

	int i = 0;
	jsig = getter_job();
	if (pid > 0)
	{
		/* Update the record for the process.  */
		job = jsig->first_job;
		while ((job = job->next))
		{
			elem = job->cmds;
			while (elem)
			{
				if (elem->pid == pid)
				{
					dprintf(1, "-<|on check le status de %d|>\n", elem->pid);
					elem->status = status;
					if (WIFSTOPPED (status))
						elem->stopped = 1;
					else
					{
						elem->completed = 1;
						if (WIFSIGNALED (status))
							elem->signal = WTERMSIG (elem->status);
					}
					dprintf(3, "-<|return 0|>\n");
					return 0;
				}
				elem = elem->next_cmd;
			}
				// fprintf(stderr, "process %d et %d\n", pid, elem->pid);
		}
		fprintf (stderr, "No child process %d et %d\n", pid, elem->pid);//debug, a supprimer apres
		return -1;
	}

	else if (pid == 0)
		/* No processes ready to report.  */
		return -1;
	else
	{
		/* Other weird errors.  */
		//perror ("waitpid");// POUR DEBUG
		return -1;
	}
}


void wait_for_job (t_job *j)
{
	int status;
	pid_t pid;
	id_t id;
	siginfo_t t;

	while (1)
	{
		// printf("-<|loop|>\n");
		pid = waitpid (j->cmds->pid, &status, WUNTRACED);
		// printf("-<|fin wait pid %d|>\n", pid);
		if (mark_process_status (pid, status))
			break ;
		// printf("-<|mark procss staus ok|>\n");
		if (job_is_stopped (j))
			break ;
		// printf("-<|job is stopped ok|>\n");
		if (job_is_completed (j))
			break ;
		// printf("-<|job is completed ok|>\n");

	}

//	do
//		pid = waitpid (WAIT_ANY, &status, WUNTRACED);
//	while (!mark_process_status (pid, status)
//		   && !job_is_stopped (j)
//		   && !job_is_completed (j));
	// printf("-<|fin wait for job|>\n");
}
