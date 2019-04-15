/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   continue_stop_job.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 19:36:34 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 19:36:34 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "shell.h"


/* Mark a stopped job J as being running again.  */

void mark_job_as_running (t_job *j)
{
	t_process *p;

	for (p = j->first_process; p; p = p->next)
		p->stopped = 0;
	j->notified = 0;
}


/* Continue the job J.  */

void continue_job (t_job *j, int foreground)
{
	mark_job_as_running (j);
	if (foreground)
		put_job_in_foreground (j, 1);
	else
		put_job_in_background (j, 1);
}
