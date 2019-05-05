/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_output.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 15:02:55 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:59:00 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	shell_set_output_file(t_output *output, t_cmd *elem, int fd_file)
{
	if (output->from == 1)
	{
		(elem->process).fd_stdout = ft_strdup(output->to);
		(elem->process).fd_fileout = fd_file;
	}
	else if (output->from == 2)
	{
		(elem->process).fd_stderr = ft_strdup(output->to);
		(elem->process).fd_fileerr = fd_file;
	}
}

void	shell_exec_print_error(t_cmd *elem)
{
	if (ft_strcmp("not found", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: command not found\n", elem->args[0]);
	else if (ft_strcmp("directory", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: Is a directory\n", elem->args[0]);
	else if (ft_strcmp("file or directory", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: No such file or directory\n",
		elem->args[0]);
	else if (ft_strcmp("no allowed", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: Permission denied\n", elem->args[0]);
}

int		shell_exec_error(t_cmd *elem)
{
	int ret;

	ret = 1;
	if (elem->exec)
	{
		shell_exec_print_error(elem);
		if (ft_strcmp("no allowed", elem->exec) == 0 ||
			ft_strcmp("directory", elem->exec) == 0)
			exit(126);
		else if (ft_strcmp("file or directory", elem->exec) == 0 ||
			ft_strcmp("not found", elem->exec) == 0)
			exit(127);
		else
			ret = 0;
	}
	return (ret);
}

void	child_signals_to_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

/*
** cmd est découpé dans les jobs
*/

void	shell_prepare_jobs(t_job *first_jobs, t_cmd *cmd)
{
	t_job	*job;
	t_cmd	*elem;

	job = first_jobs;
	while ((job->next))
		job = job->next;
	elem = cmd->next_cmd;
	shell_prepare_jobs_boucle(elem, first_jobs, job);
	free(cmd->start);
}
