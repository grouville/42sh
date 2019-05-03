/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_export.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 17:33:02 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 00:40:44 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
*** - Aim of the function :
*** - Prompt the proper error for the jobs -l error
*/

void		output_sig(int sig, char **signal_output)
{
	if (sig == 21)
		*signal_output = ft_strdup("(tty output):");
	else if (sig == 22)
		*signal_output = ft_strdup("(tty input):");
	else
		*signal_output = ft_strdup("Error unknown:");
}

/*
*** - Aim of the function :
*** - Print all the infos for the jobs -l command
*** - when the job has had a specific signal printing
*** - (Killed by signal X or the reason why the job in bg is stopped)
*/

void		format_job_info_signal_l_option(t_job *j,
				const char *status, int sig)
{
	int		i;
	t_cmd	*elem;
	char	*signal_output;

	signal_output = NULL;
	output_sig(sig, &signal_output);
	ft_dprintf(1, "[%d]+ %d %-2s %s %d ", j->num, j->pgid, status,
		signal_output, sig);
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
	free(signal_output);
	ft_dprintf(1, "\n");
}

/*
*** - Aim of the function :
*** - Format all the normal -l option for the jobs builtin
*/

void		format_job_info_l_option(t_job *j, const char *status)
{
	int		i;
	t_cmd	*elem;

	ft_dprintf(1, "[%d]+ %d %-10s", j->num, j->pgid, status);
	elem = j->cmds;
	while (elem)
	{
		i = 0;
		while (elem->args[i])
			ft_dprintf(1, "%s ", elem->args[i++]);
		if (elem->next_cmd)
		{
			print_sep(1, elem->sep);
			ft_dprintf(1, " ");
		}
		elem = elem->next_cmd;
	}
	ft_dprintf(1, "\n");
}

/*
*** - Aim of the function :
*** - Sends the -l option to the proper printing function
*/

void		process_jobs_option_l(t_job **job)
{
	if (job_is_completed(*job))
	{
		if (job_is_signaled(*job))
			format_job_info_l_option(*job, "Killed:");
		else
			format_job_info_l_option(*job, "Done");
		free_job_after_signal(job);
	}
	else if (job_is_stopped(*job) && (*job)->running != 0
		&& (*job)->running != 999)
	{
		format_job_info_signal_l_option(*job, "Stopped", (*job)->running);
		(*job)->notified = 1;
	}
	else
		format_job_info_l_option(*job, "Running");
}
