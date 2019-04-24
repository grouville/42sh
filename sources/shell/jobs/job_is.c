/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_is.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 22:53:51 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 22:53:51 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "shell.h"

t_job *find_job(pid_t pgid)
{
	t_job	*j;
	t_js	*jsig;

	jsig = getter_job();
	j = jsig->first_job;
	while (j)
	{
		if (j->pgid == pgid)
			return (j);
		j = j->next;
	}
	// for (j = jsig->first_job; j; j = j->next)
	// 	if (j->pgid == pgid)
	// 		return j;
	return (NULL);
}

/*
** Return true if all processes in the job have stopped or completed.
*/

int job_is_stopped(t_job *j)
{
	t_cmd *p;

	p = j->cmds;
	while (p)
	{
		if (!p->stopped)
		{
			printf("-<|job is not stopped|>\n");
			return (0);
		}
		p = p->next_cmd;
	}
	return (1);
}

/*
** Return true if all processes in the job have completed.
*/

int job_is_completed(t_job *j)
{
	t_cmd *p;

	p = j->cmds;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next_cmd;
	}
	return (1);
}

/*
*** - Aim of the function :
** - If one of the process in the job has been killed by a signal
*** - returns the corresponding signal
*/

int	job_is_signaled(t_job *j)
{
	t_cmd *p;

	p = j->cmds;
	while (p)
	{
		if (p->signal)
			return (p->signal);
		p = p->next_cmd;
	}
	return (0);
}