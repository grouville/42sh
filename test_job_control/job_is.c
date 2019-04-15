/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_is.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 19:41:06 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 19:41:06 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "shell.h"

job *find_job (pid_t pgid)
{
	job *j;

	for (j = first_job; j; j = j->next)
		if (j->pgid == pgid)
			return j;
	return NULL;
}


/* Return true if all processes in the job have stopped or completed.  */
int job_is_stopped (job *j)
{
	process *p;

	for (p = j->first_process; p; p = p->next)
		if (!p->completed && !p->stopped)
			return 0;
	return 1;
}


/* Return true if all processes in the job have completed.  */
int job_is_completed (job *j)
{
	process *p;

	for (p = j->first_process; p; p = p->next)
		if (!p->completed)
			return 0;
	return 1;
}
