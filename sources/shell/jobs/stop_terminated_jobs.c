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

/*
** Check for processes that have status information available, without blocking
*/

void	update_status(void)
{
	int status;
	pid_t pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!mark_process_status (pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
}


void	print_sep(int fd, t_sep sep)
{
	if (sep == 1)
		ft_dprintf(fd, "|");
	else if (sep == 2)
		ft_dprintf(fd, ";");
	else if (sep == 3)
		ft_dprintf(fd, "||");
	else if (sep == 4)
		ft_dprintf(fd, "&&");
	else if (sep == 5)
		ft_dprintf(fd, "&");
}
/*
** Format information about job status for the user to look at.
*/

void	format_job_info(t_job *j, const char *status, int nb_bgjob)
{
	int		i;
	t_cmd	*elem;

	ft_dprintf(1, "[%d]+ %-10s", nb_bgjob, status);
	elem = j->cmds;
	while (elem)
	{
		i = 0;
		while (elem->args_raw[i])
			ft_dprintf(1, "%s ", elem->args_raw[i++]);
		if (elem->next_cmd)
		{
			print_sep(1, elem->sep);
			ft_dprintf(1, " ");
		}
		elem = elem->next_cmd;
	}
	ft_dprintf(1, "\n");
}

void	free_job(t_job **j, t_cmd **cmd)
{
	if (cmd)
		*cmd = NULL;
	clean_cmd(&(*j)->cmds);
	free(*j);
	*j = NULL;
}

void format_job_info_signal(t_job *j, const char *status, int nb_bgjob)
{
	int 	i;
	t_cmd	*elem;

	i = -1;
	ft_dprintf(1, "[%d]+ %-2s %-4d", nb_bgjob, status, job_is_signaled(j));
	elem = j->cmds;
	while (elem)
	{
		i = 0;
		while (elem->args_raw[i])
			ft_dprintf(1, "%s ", elem->args_raw[i++]);
		if (elem->next_cmd)
		{
			print_sep(1, elem->sep);
			ft_dprintf(1, " ");
		}
		elem = elem->next_cmd;
	}
	ft_dprintf(1, "\n");
}

/*
*** - Aim of the function :
*** - Returns true if the job begins with the "jobs" command
*** - Need to check if it is any command
*/

int		check_last_command_jobs(t_cmd **cmd)
{
	t_cmd		*elem;

	elem = *cmd;
	while ((elem = elem->next_cmd))
		if (elem->args && elem->args[0] &&
				ft_strcmp(elem->args[0], "jobs") == 0 &&
			elem->done == 0)
			return (1);
	return (0);
}


int		check_last_command_fc(void)
{
	t_job		*j;
	t_cmd		*elem;
	BOOL		is_jobs;

	j = getter_job()->first_job;
	is_jobs = 0;
	while ((j = j->next))
	{
		elem = j->cmds;
		while (elem)
		{
			if (elem->args && elem->args[0] &&
					ft_strcmp(elem->args[0], "fc") == 0)
				is_jobs = 1;
			elem = elem->next_cmd;
		}
	}
	// printf("isjobs: %d\n", is_jobs);
	return (is_jobs);
}

/*
** Notify the user about stopped or terminated jobs.
** Delete terminated jobs from the active job list.
*/

void do_job_notification(t_cmd **cmd, t_shell *shl, t_cmd **cmd_jobs)
{
	t_job		*j;
	t_job		*jnext;
	t_job		*jprev;
	t_js		*jsig;

	jsig = getter_job();
	/* Update status information for child processes.  */
	update_status();
	/* Manage the printing of the do_job_notification or not (will be managed by the job builtin) */
	if (shl->str && (check_last_command_jobs(cmd_jobs) || check_last_command_fc()))
		return ;
	jprev = jsig->first_job;
	j = jsig->first_job;
	while ((j = j->next))
	{
		jnext = j->next;
//		printf("-<do job notif %s|%d|>pgid = %d\n", j->cmds->args[0], j->cmds->done, j->pgid);
		if (j->pgid == 0)
		{
			if (job_is_completed(j))
			{
				jprev->next = jnext;
				if (j == jsig->first_job)
					jsig->first_job = jsig->first_job->next;
				//printf("-<|on free %s|>\n", j->cmds->args[0]);
				free_job(&j, cmd);
				j = jprev;
			}
			jprev = j;
			continue ;
		}
		// jnext = j->next;
		/* If all processes have completed, tell the user the job has
		   completed and delete it from the list of active jobs.  */
		if (j->sep == SPL_SPRLU && job_is_completed(j))
		{
			if (job_is_signaled(j))
				format_job_info_signal(j, "Killed:", j->num);
			else
				format_job_info(j, "Done", j->num);
			// if (j == jsig->first_job)
			// 	jsig->first_job = jsig->first_job->next;
			jprev->next = jnext;
			free_job (&j, cmd);
			j = jprev;
			continue ;
		}
		/* Notify the user about stopped jobs,
		 * marking them so that we won’t do this more than once.  */
		else if (j->sep == SPL_SPRLU && job_is_stopped (j) && !j->notified && j->running)
		{
			if (cmd)
				*cmd = NULL;
			if (j->notified_crtrz == 0)
				format_job_info(j, "Stopped", j->num);
			j->notified = 1;
		}

		/* Don’t say anything about jobs that are still running.  */
		jprev = jprev->next;
	}
}
