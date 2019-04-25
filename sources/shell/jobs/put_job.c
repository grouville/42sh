/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   put_job.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/17 23:01:39 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 23:01:39 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "shell.h"

/* Put job j in the foreground.  If cont is nonzero,
   restore the saved terminal modes and send the process group a
   SIGCONT signal to wake it up before we block.  */

void put_job_in_foreground (t_job *j, int cont)
{
	t_js	*jsig;

	jsig = getter_job();
	/* Put the job into the foreground.  */
	tcsetpgrp (jsig->shell_terminal, j->pgid);


	/* Send the job a continue signal, if necessary.  */
	if (cont)
	{
		tcsetattr (jsig->shell_terminal, TCSADRAIN, &j->tmodes);
		if (kill (- j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}

	/* Wait for it to report.  */
	wait_for_job (j);
	/* Put the shell back in the foreground.  */
	tcsetpgrp (jsig->shell_terminal, jsig->shell_pgid);
	/* Restore the shell’s terminal modes.  */
	tcgetattr (jsig->shell_terminal, &j->tmodes);
	tcsetattr (jsig->shell_terminal, TCSADRAIN, &(jsig->shell_tmodes));
}

/* Put a job in the background.  If the cont argument is true, send
   the process group a SIGCONT signal to wake it up.  */

void put_job_in_background (t_job *j, int cont)
{
	ft_dprintf(1, "[%d] %d\n", count_job_bg() + 1, j->pgid);
	/* Send the job a continue signal, if necessary.  */
	if (cont)
		if (kill (-j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
//	if (cont)
//	if (kill (-j->pgid, SIGTTIN) < 0)
//		perror ("kill (SIGCONT)");
}

void put_job_suspended(t_job *j)
{
	t_js	*jsig;
	t_cmd	*elem;

//	ft_dprintf(1, "[%d]  + %d suspended")
	j->sep = SPL_SPRLU;
	elem = j->
	do_job_notification();
	jsig = getter_job();
	tcsetpgrp (jsig->shell_terminal, jsig->shell_pgid);
	/* Restore the shell’s terminal modes.  */
	tcgetattr (jsig->shell_terminal, &j->tmodes);
	tcsetattr (jsig->shell_terminal, TCSADRAIN, &(jsig->shell_tmodes));
}