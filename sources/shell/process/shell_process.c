/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/28 20:39:43 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/28 20:39:57 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
** ATTENTION shell->str peut etre vide apres un heredoc
*/

#include "shell.h"

/*
** return 0 pour passer au job suivant
** return 1 pour passer à la commande suivante
** return -1 dans le cas d'un exit confirmé
*/

int 	shell_process_cmd(t_cmd **elem, t_shell *shell)
{
	int exec;
	int fd[3];

	if (!shell_prepare_args(*elem, shell))
		return (0);
	read_lexing(*elem);
	shell_save_fd(fd);
	if ((*elem)->sep == SPL_PIPE)
		exec = shell_exec_pipes(elem, shell);
	else
		exec = shell_exec(*elem, shell);
	shell_reinit_fd(fd);
	shell_ret(*elem, shell);
	if (exec == -1)
		return (-1);
	else if (exec == EXIT_SUCCESS && (*elem)->sep == DBL_PIPE)
		*elem = shell_process_skip_cmd(*elem, DBL_PIPE);
	else if (exec > 0 && (*elem)->sep == DBL_SPRLU)
		*elem = shell_process_skip_cmd(*elem, DBL_SPRLU);
	else if ((*elem)->sep == 0)
		return (0);
	return (1);
}

void 	launch_process(t_cmd *elem, pid_t pgid,
					   int infile, int outfile, int errfile,
					   int foreground)
{
	pid_t pid;

	if (shell_is_interactive)
	{
		/* Put the process into the process group and give the process group
		   the terminal, if appropriate.
		   This has to be done both by the shell and in the individual
		   child processes because of potential race conditions.  */
		pid = getpid ();
		if (pgid == 0)
			pgid = pid;
		setpgid (pid, pgid);
		if (foreground)
			tcsetpgrp (shell_terminal, pgid);

		/* Set the handling for job control signals back to the default.  */
		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		signal (SIGTSTP, SIG_DFL);
		signal (SIGTTIN, SIG_DFL);
		signal (SIGTTOU, SIG_DFL);
		signal (SIGCHLD, SIG_DFL);
	}

	/* Exec the new process.  Make sure we exit.  */
	execvp (elem->args[0], elem->args);
	perror ("execvp");
	exit (1);
}

int		launch_job(t_job *job, t_shell *shell, int foreground)
{
	t_cmd	*elem;
	pid_t	pid;
	//t_job	*free_jobs;
	int 	mypipe[2];
	int		infile;
	int		outfile;

	// printf("-<lunch job shell interactive:|%d| avant_plan:|%d|>\n", shell_is_interactive, foreground);
	infile = job->stdin;
	elem = job->cmds;
	while (elem)
	{
		if (elem->next_cmd)
		{
			if (pipe (mypipe) < 0)
			{
				perror ("pipe");
				exit (1);
			}
			outfile = mypipe[1];
		}
		else
			outfile = job->stdout;

		pid = fork ();
		if (pid == 0)
			launch_process(elem, job->pgid, infile, outfile, job->stderr, foreground);
		else if (pid < 0)
		{
			/* The fork failed. */
			perror ("fork");
			exit (1);
		}
		else
		{
			/* This is the parent process. */
			elem->pid = pid;
			if (shell_is_interactive)
			{
				if (!job->pgid)
					job->pgid = pid;
				setpgid (pid, job->pgid);
			}
		}

		/* Clean up after pipes. */
		/*if (infile != job->stdin)
			close (infile);
		if (outfile != job->stdout)
			close (outfile);
		infile = mypipe[0];
*/
		/*
		ret = shell_process_cmd(&elem, shell);
		if (ret == 0)
			break;
		else if (ret == -1)
		{
			//return (clean_jobs(&free_jobs));
			return (1);
		}*/
		elem = elem->next_cmd;
	}

	ft_dprintf(2, "%ld (launched): %s\n", (long)job->pgid, job->cmds->args[0]);
	if (!shell_is_interactive)
		wait_for_job (job);
	else if (foreground)
		put_job_in_foreground (job, 0);
	else
		put_job_in_background (job, 0);
	return (1);
}


int		shell_process(t_job *jobs, t_cmd **cmd, t_shell *shell)
{

	int 	ret;
	int 	forground;
	t_job	*job;

	//Toujours nécessaire d'intercepter Ctrl-C ?
	//signal(SIGINT, shell_prcs_sigint);
	do_job_notification();
	shell_prepare(jobs, *cmd);
	//free_jobs = jobs;
	job = jobs;
	while ((job = job->next))
	{
		// printf("-<state|%d|>\n", job->state);
		if (job->state != -1) //on lance que les new jobs pas en background
		{
			forground = (job->sep) == SPL_SPRLU ? 0 : 1;
			ret = launch_job(job, shell, forground);
			job->state = -1; // mettre à -1 pour qu'ils ne soient plus exécutés par la suite
			// do_job_notification();
		}
	}
	//shell_clean_data(cmd, shell, 1);
	return (1);
}


void	read_lexing(t_cmd *elem)
{
	t_output	*read;
	int 		i;

	ft_dprintf(2, "-------------\n");
	ft_dprintf(2, "Read exec : %s\n", elem->exec);
	i = 0;
	ft_dprintf(2, "Read arraw : ");
	while (elem->args_raw && elem->args_raw[i])
	{
		ft_dprintf(2, "arg[%i]=<%s> ", i, elem->args_raw[i]);
		i++;
	}
	i = 0;
	ft_dprintf(2, "\nRead array : ");
	while (elem->args && elem->args[i])
	{
		ft_dprintf(2, "arg[%i]=<%s> ", i, elem->args[i]);
		i++;
	}
	ft_dprintf(2, "\nRead output : ");
	read = elem->output;
	if (read == NULL)
		ft_dprintf(2, "(NULL)");
	while (read != NULL)
	{
		ft_dprintf(2, "from %d to <%s> append=%d - ", read->from, read->to, read->append);
		read = read->next;
	}
	ft_dprintf(2, "\nRead input : ");
	if (!elem->input)
		ft_dprintf(2, "(NULL)");
	i = 0;
	while (elem->input && (elem->input)[i] != NULL)
	{
		if ((int)(elem->input)[i] <= -1 && (int)(elem->input)[i] >= -3)
			ft_dprintf(2, "|%d| -", (int)(elem->input)[i++]);
		else
			ft_dprintf(2, "|%s| - ", (elem->input)[i++]);
	}
	ft_dprintf(2, "\nRead hrdc : ");
	if (!elem->hrdc)
		ft_dprintf(2, "(NULL)");
	i = 0;
	while (elem->hrdc && (elem->hrdc)[i] != NULL)
	{
		if ((int)(elem->hrdc)[i] <= -1 && (int)(elem->hrdc)[i] >= -3)
			ft_dprintf(2, "|%d| -", (int)(elem->hrdc)[i++]);
		else
			ft_dprintf(2, "|%s| - ", (elem->hrdc)[i++]);
	}
	if ((int)(elem->process).stdin_send == -1 || (int)(elem->process).stdin_send == -2)
		ft_dprintf(2, "\nRead stdin : |%d|\n", (int)elem->process.stdin_send);
	else
		ft_dprintf(2, "\nRead stdin : |%s|\n", elem->process.stdin_send);
	ft_dprintf(2, "Read fd stdin : |%s|\n", elem->process.fd_stdin);
	ft_dprintf(2, "Read fd stdout : |%s|\n", elem->process.fd_stdout);
	ft_dprintf(2, "Read fileout : |%d|\n", elem->process.fd_fileout);
	ft_dprintf(2, "Read fd stderr : |%s|\n", elem->process.fd_stderr);
	ft_dprintf(2, "Read fileerr : |%d|\n", elem->process.fd_fileerr);
	ft_dprintf(2, "Et sep %d\n", elem->sep);
	ft_dprintf(2, "-------------\n");
}