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
	return (is_jobs);
}
