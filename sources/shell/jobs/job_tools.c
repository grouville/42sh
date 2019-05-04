/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stop_terminated_jobs.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 18:25:51 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 19:26:01 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** Check for processes that have status information available, without blocking
*/

void	update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}

void	print_sep(int fd, t_sep sep)
{
	if (sep == 1)
		ft_dprintf(fd, "|");
	else if (sep == 2)
		ft_dprintf(fd, ";");
	else if (sep == 3)
		ft_dprintf(fd, "||");
	else if (sep == 4)
		ft_dprintf(fd, "&&");
	else if (sep == 5)
		ft_dprintf(fd, "&");
}

/*
** Format information about job status for the user to look at.
*/

void	format_job_info(t_job *j, const char *status, int nb_bgjob)
{
	int		i;
	t_cmd	*elem;

	ft_dprintf(1, "[%d]+ %-10s", nb_bgjob, status);
	elem = j->cmds;
	while (elem)
	{
		i = 0;
		while (elem->args_raw[i])
			ft_dprintf(1, "%s ", elem->args_raw[i++]);
		if (elem->next_cmd)
		{
			print_sep(1, elem->sep);
			ft_dprintf(1, " ");
		}
		elem = elem->next_cmd;
	}
	ft_dprintf(1, "\n");
}

void	free_job(t_job **j, t_cmd **cmd)
{
	if (cmd)
		*cmd = NULL;
	clean_cmd(&(*j)->cmds);
	free(*j);
	*j = NULL;
}

void	format_job_info_signal(t_job *j, const char *status, int nb_bgjob)
{
	int		i;
	t_cmd	*elem;

	i = -1;
	ft_dprintf(1, "[%d]+ %-2s %-4d", nb_bgjob, status, job_is_signaled(j));
	elem = j->cmds;
	while (elem)
	{
		i = 0;
		while (elem->args_raw[i])
			ft_dprintf(1, "%s ", elem->args_raw[i++]);
		if (elem->next_cmd)
		{
			print_sep(1, elem->sep);
			ft_dprintf(1, " ");
		}
		elem = elem->next_cmd;
	}
	ft_dprintf(1, "\n");
}
