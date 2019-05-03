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
** return -2 dans le cas de bad subsitution --> cancel cmd
*/

int 	shell_process_cmd(t_cmd **elem, t_shell *shell, t_job *job)
{
	int fd[3];

	(*elem)->done = 1;
	shell_prepare_args(*elem, shell);
	//read_lexing(*elem);
	shell_save_fd(fd);
	if ((*elem)->sep == SPL_PIPE)
		(*elem)->ret = shell_exec_pipes(elem, shell, job);
	else if (!(*elem)->bad_substitution)
		(*elem)->ret = shell_exec(*elem, shell, job);
	shell_reinit_fd(fd);
	shell_ret(*elem, shell);
	if ((*elem)->bad_substitution)
		return (-2);
	if ((*elem)->ret == -1)
		return (-1);
	else if ((*elem)->ret == EXIT_SUCCESS && (*elem)->sep == DBL_PIPE)
		*elem = shell_process_skip_cmd(*elem, DBL_PIPE);
	else if (shell->ret > 0 && (*elem)->sep == DBL_SPRLU)
		*elem = shell_process_skip_cmd(*elem, DBL_SPRLU);
	else if ((*elem)->sep == 0)
		return (0);
	return (1);
}



int		launch_job(t_job *job, t_shell *shell)
{
	t_cmd	*elem;
	t_js	*jsig;
	BOOL	suspended;
	int 	ret;

	suspended = 0;
	jsig = getter_job();
	elem = job->cmds;
	while (elem)
	{
		ret = shell_process_cmd(&elem, shell, job);
		if (ret == -1)
			return (-1);
		else if (ret == -2)
			return (-2);
		if (elem->ret == 4735 && (suspended = 1)) //4735 ret status d'un Ctrl-Z
			put_process_suspended(job, elem);
		elem = elem->next_cmd;
	}
	if (!jsig->shell_is_interactive)
		wait_for_job (job);
	else if (job->sep != SPL_SPRLU)
		put_job_in_foreground(job, 0);
	else if (!suspended)
		put_job_in_background(job, 0);
	return (1);
}

void	shell_skip_job(t_job *job)
{
	t_cmd *elem;

	while (job)
	{
		elem = job->cmds;
		while (elem)
		{
			elem->done = 1;
			elem = elem->next_cmd;
		}
		job = job->next;
	}
}

int		shell_process(t_job *jobs, t_cmd **cmd, t_shell *shell)
{
	int 	ret;
	t_job	*job;

	do_job_notification(NULL, shell);
	shell_prepare(jobs, *cmd);
	job = jobs;
	while ((job = job->next))
	{
		if (job->state != -1) //on lance que les new jobs pas en background
		{
			ret = launch_job(job, shell);
			job->state = -1;
			if (ret == -1)
				return (-1);
			else if (ret == -2)
			{
				shell_skip_job(job);
				break ;
			}
		}
	}
	ft_strdel(&shell->str);
	ft_strdel(&shell->hrdc_tmp);
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