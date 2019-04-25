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

/*
*** - Aim of the function :
*** - wait only used when fg and bg are being processed
*/

void wait_for_job_fg_bg(t_job *j)
{
	int status;
	pid_t pid;
	id_t id;
	siginfo_t t;

	while (1)
	{
		// printf("-<|loop|>\n");  j->cmds->pid
		pid = waitpid (WAIT_ANY, &status, WUNTRACED);
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
}

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
		wait_for_job_fg_bg(j);
	}
	else
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
	ft_dprintf(1, "[%d] %d\n", count_job_bg(), j->pgid);
	/* Send the job a continue signal, if necessary.  */
	if (cont)
		if (kill (-j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
//	if (cont)
//	if (kill (-j->pgid, SIGTTIN) < 0)
//		perror ("kill (SIGCONT)");
}

void put_process_suspended(t_job *j, t_cmd *elem)
{
	t_js	*jsig;

//	ft_dprintf(1, "[%d]  + %d suspended")
	j->sep = SPL_SPRLU;
	elem->stopped = 1;
	printf("-<|1|>\n");
	ft_dprintf(1, "[%d]+  %-10s%s\n", count_job_bg(), "Stopped", elem->args[0]);
//	do_job_notification();
	printf("-<|2|>\n");
	jsig = getter_job();
	tcsetpgrp (jsig->shell_terminal, jsig->shell_pgid);
	/* Restore the shell’s terminal modes.  */
	tcgetattr (jsig->shell_terminal, &j->tmodes);
	tcsetattr (jsig->shell_terminal, TCSADRAIN, &(jsig->shell_tmodes));

}