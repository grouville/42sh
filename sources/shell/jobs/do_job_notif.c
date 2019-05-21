/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stop_terminated_jobs.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 18:25:51 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 19:14:29 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		free_zombies(t_cmd **cmd, t_job **j, t_job **jnext, t_job **jprev)
{
	t_js		*jsig;

	jsig = getter_job();
	if (job_is_completed(*j))
	{
		(*jprev)->next = *jnext;
		if (*j == jsig->first_job)
			jsig->first_job = jsig->first_job->next;
		free_job(j, cmd);
		*j = *jprev;
	}
	*jprev = *j;
	return (0);
}

int		free_done(t_cmd **cmd, t_job **j, t_job **jnext, t_job **jprev)
{
	if (job_is_signaled(*j))
		format_job_info_signal(*j, "Killed:", (*j)->num);
	else
		format_job_info(*j, "Done", (*j)->num);
	(*jprev)->next = *jnext;
	free_job(j, cmd);
	*j = *jprev;
	return (0);
}

int		notify_stop(t_cmd **cmd, t_job **j)
{
	if (cmd)
		*cmd = NULL;
	if ((*j)->notified_crtrz == 0)
		format_job_info(*j, "Stopped", (*j)->num);
	(*j)->notified = 1;
	return (0);
}

/*
** Notify the user about stopped or terminated jobs.
** Delete terminated jobs from the active job list.
*/

void	do_job_notification(t_cmd **cmd, t_shell *shl, t_cmd **cmd_jobs)
{
	t_job		*j;
	t_job		*jnext;
	t_job		*jprev;

	update_status();
	if (shl->str && (check_last_command_jobs(cmd_jobs)
		|| check_last_command_fc()))
		return ;
	jprev = getter_job()->first_job;
	j = getter_job()->first_job;
	while ((j = j->next))
	{
		jnext = j->next;
		if (j->pgid == 0 && !free_zombies(cmd, &j, &jnext, &jprev))
			continue ;
		if (j->sep == SPL_SPRLU && job_is_completed(j)
			&& !free_done(cmd, &j, &jnext, &jprev))
			continue ;
		else if (j->sep == SPL_SPRLU && job_is_stopped(j)
			&& !j->notified && j->running && j->running != 999)
			notify_stop(cmd, &j);
		jprev = jprev->next;
	}
}
