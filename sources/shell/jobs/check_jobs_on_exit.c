/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/16 11:01:40 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 18:36:59 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
*** - Aim of the function :
*** - Check jobs on exit. If one is stopped, returns 1
*/

int		check_any_stopped_job_left(void)
{
	t_js		*jsig;
	t_job		*job;
	t_cmd		*elem;

	jsig = getter_job();
	job = jsig->first_job;
	while (job)
	{
		elem = job->cmds;
		while (elem)
		{
			if (elem->stopped && !elem->done)
				return (1);
			elem = elem->next_cmd;
		}
		job = job->next;
	}
	return (0);
}

void	kill_all_processes(void)
{
	t_js		*jsig;
	t_job		*job;
	t_cmd		*elem;

	jsig = getter_job();
	job = jsig->first_job;
	while (job)
	{
		elem = job->cmds;
		while (elem)
		{
			if (elem->stopped && !elem->done)
				kill(elem->pid, SIGKILL);
			elem = elem->next_cmd;
		}
		job = job->next;
	}
}

/*
*** - Aim of the function :
*** - Check jobs on exit. If one is stopped, returns 1
*/

int		check_jobs_on_exit(t_shell *shl)
{
	static int	boul = 0;
	int			is_stopped;

	is_stopped = check_any_stopped_job_left();
	if (is_stopped && !boul)
	{
		ft_dprintf(2, "there are stopped jobs left\n");
		ft_strdel(&shl->str);
		boul++;
		return (1);
	}
	else if (is_stopped && boul)
		kill_all_processes();
	return (0);
}
