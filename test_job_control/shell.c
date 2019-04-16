/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 18:59:36 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 18:59:36 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"


/* Make sure the shell is running interactively as the foreground job
   before proceeding. */

void init_shell ()
{

	/* See if we are running interactively.  */
	shell_terminal = STDIN_FILENO;
	shell_is_interactive = isatty (shell_terminal);

	if (shell_is_interactive)
	{
		/* Loop until we are in the foreground.  */
		while (tcgetpgrp (shell_terminal) != (shell_pgid = getpgrp ()))
			kill (- shell_pgid, SIGTTIN);

		/* Ignore interactive and job-control signals.  */
		signal (SIGINT, SIG_IGN);
		signal (SIGQUIT, SIG_IGN);
		signal (SIGTSTP, SIG_IGN);
		signal (SIGTTIN, SIG_IGN);
		signal (SIGTTOU, SIG_IGN);
		signal (SIGCHLD, SIG_IGN);

		/* Put ourselves in our own process group.  */
		shell_pgid = getpid ();
		if (setpgid (shell_pgid, shell_pgid) < 0)
		{
			printf("Couldn't put the shell in its own process group");
			exit (1);
		}

		/* Grab control of the terminal.  */
		tcsetpgrp (shell_terminal, shell_pgid);

		/* Save default terminal attributes for shell.  */
		tcgetattr (shell_terminal, &shell_tmodes);
	}
}

int mygetch ( void )
{
	int ch;
	struct termios oldt, newt;

	tcgetattr ( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

	return ch;
}

t_process	*create_process()
{
	t_process *ret;
	t_process *process = malloc(sizeof(t_process));
	ret = process;
	bzero(process, sizeof(t_process));
	process->argv = malloc(sizeof(char *) * 3);
	process->argv[0] = strdup("cat");
	process->argv[1] = strdup("ok");
	process->argv[1] = NULL;
	t_process *process2 = malloc(sizeof(t_process));
	process->next = process2;
	bzero(process2, sizeof(t_process));
	process2->argv = malloc(sizeof(char *) * 3);
	process2->argv[0] = strdup("vim");
	process2->argv[1] = strdup("ok2");
	process2->argv[1] = NULL;

/*
	process->next = malloc(sizeof(t_process));
	process = process->next;
	bzero(process, sizeof(t_process));
	char *str3[2];
	str3[0] = "vim";
	str3[1] = NULL;
	process->argv = str;*/
	return (ret);
}

int     main(int ac, char **av)
{
    init_shell();

	t_process *process = create_process();
    t_job *job = malloc(sizeof(t_job));
    bzero(job, sizeof(t_job));
    job->command = "test";
    job->first_process = process;
    job->stdin = 0;
    job->stdout = 1;
    job->stderr = 2;

	first_job = job;
    launch_job(job, 0);
	//printf("-<|press touch|>\n");
	mygetch();
	do_job_notification();
	mygetch();
	//put_job_in_foreground(job, 1);
	//printf("-<|fin|>\n");
//	launch_job(job, 1);

//    process->pid = 0;
//    process->completed = 0;
//    process->stopped = 0;
//    process->status = 0;
    return (1);
}