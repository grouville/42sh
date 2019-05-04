/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/28 20:39:43 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 20:43:08 by gurival-    ###    #+. /#+    ###.fr     */
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

int		shell_process_cmd(t_cmd **elem, t_shell *shell, t_job *job)
{
	int fd[3];

	(*elem)->done = 1;
	shell_prepare_args(*elem, shell);
	shell_save_fd(fd);
	if ((*elem)->sep == SPL_PIPE)
		(*elem)->ret = shell_exec_pipes(elem, shell, job);
	else if (!(*elem)->bad_substitution)
		(*elem)->ret = shell_exec(*elem, shell, job);
	shell_reinit_fd(fd);
	if ((*elem)->ret == -1)
		return (-1);
	shell_ret(*elem, shell);
	if ((*elem)->bad_substitution)
		return (-2);
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
	BOOL	suspended;
	int		ret;

	suspended = 0;
	elem = job->cmds;
	while (elem)
	{
		ret = shell_process_cmd(&elem, shell, job);
		if (ret == -1)
			return (-1);
		else if (ret == -2)
			return (-2);
		if (elem->ret == 4735 && (suspended = 1))
			put_process_suspended(job, elem);
		elem = elem->next_cmd;
	}
	if (!getter_job()->shell_is_interactive)
		wait_for_job(job);
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
	int		ret;
	t_job	*job;

	do_job_notification(NULL, shell, cmd);
	shell_prepare(jobs, *cmd);
	job = jobs;
	while ((job = job->next))
	{
		if (job->state != -1)
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
	*cmd = NULL;
	ft_strdel(&shell->str);
	ft_strdel(&shell->hrdc_tmp);
	return (1);
}
