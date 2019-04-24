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

void format_job_info(t_job *j, const char *status, int nb_bgjob)
{
	int i;
	int job_pos;

	i = -1;
	ft_dprintf(1, "[%d]+ %-10s", nb_bgjob, status);
	while (j->cmds->args_raw[++i])
		ft_dprintf(1, "%s ", j->cmds->args_raw[i]);
	ft_dprintf(1, "\n");
	// fprintf (stderr, "%ld (%s): %s\n", (long)j->pgid, status, j->command);
}

int		count_job_bg(void)
{
	t_job	*j;
	int 	nb_jobbg;
	t_js	*jsig;

	nb_jobbg = 0;
	jsig = getter_job();
	j = jsig->first_job;
	while ((j = j->next))
	{
		if (j->sep == SPL_SPRLU && j->state == -1)
			nb_jobbg += 1;
	}
	return (nb_jobbg);
}

void	free_job(t_job *j)

{
	clean_cmd(&((j)->cmds));
	free(j);
}



/* Notify the user about stopped or terminated jobs.
   Delete terminated jobs from the active job list.  */

void do_job_notification(void)
{
	t_job	*j;
	t_job	*jnext;
	t_job	*jprev;
	t_cmd	*p;
	int		nb_bgjob;
	t_js	*jsig;

	jsig = getter_job();
	/* Update status information for child processes.  */
	update_status();
	nb_bgjob = 0;
	jprev = jsig->first_job;
	j = jsig->first_job;
	while ((j = j->next))
	{
		if (j->pgid == 0 && (jprev = j))
			continue ;
		if (j->sep == SPL_SPRLU && j->state == -1)
			nb_bgjob += 1;
		jnext = j->next;
		/* If all processes have completed, tell the user the job has
		   completed and delete it from the list of active jobs.  */
		if (j->sep == SPL_SPRLU && job_is_completed(j))
		{
			format_job_info(j, "Done", nb_bgjob);
			if (j == jsig->first_job)
				jsig->first_job = jsig->first_job->next;
			jprev->next = jnext;
			free_job (j);
			j = jprev;
			continue ;
		}
		/* Notify the user about stopped jobs,
		 * marking them so that we won’t do this more than once.  */
		else if (j->sep == SPL_SPRLU && job_is_stopped (j) && !j->notified)
		{
			format_job_info(j, "Stopped", nb_bgjob);
			j->notified = 1;
		}
		/* Don’t say anything about jobs that are still running.  */
		jprev = jprev->next;
	}
}
