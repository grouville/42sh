/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_jobs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/03 00:37:25 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 00:43:59 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
*** - Aim of the function :
*** - checks if the av is correct
*** - Then : keeps the letter of the last option set (*begin)
*** - Also :
*** - Keeps the position of the av I need to start looping on
*** - If jobs is the only arg, we return the position 1, in order to
*** - process the < process_jobs_alone > function
*** - Otherwise, we return the i - 1 in order to loop on the jobs
*/

int		ft_normalize_av(char ***av, char *c, int *begin,
					BOOL *other_arg)
{
	int		i;
	int		count;

	i = 0;
	*other_arg = 0;
	*c = 0;
	count = ft_len_array_char(*av);
	*begin = ft_len_array_char(*av);
	while (++i < count)
	{
		if ((*av)[i][0] == '-' && !ft_usage_is_good("pl", (*av)[i]))
			*c = (*av)[i][ft_strlen((*av)[i]) - 1];
		else if (((*av)[i][0] != '-') && (*other_arg = 1))
			break ;
		else if (!ft_strcmp("-", (*av)[i]))
			break ;
		else
			return (ft_usage_error("jobs: usage: jobs [-lp] [jobspec ...]",
				1));
	}
	*begin = i - 1;
	return (0);
}

/*
*** - Aim of the function :
*** - Process the job when no option has been specified
*** - If job is stated as complete, we signal the "killed"
*** - or "done" status, then we free
*** - If it is stopped, we specify and set it as Stopped
*** - Lastly, it means that the job is in bg but running
*/

void			process_jobs_without_options(t_job **job)
{
	if (job_is_completed(*job))
	{
		if (job_is_signaled(*job))
			format_job_info_signal(*job, "Killed:", (*job)->num);
		else
			format_job_info(*job, "Done", (*job)->num);
		free_job_after_signal(job);
	}
	else if (job_is_stopped(*job) && (*job)->running != 0)
	{
		format_job_info(*job, "Stopped", (*job)->num);
		(*job)->notified = 1;
	}
	else
		format_job_info(*job, "Running", (*job)->num);
}

/*
*** - Aim of the function :
*** - We print the pgid of the job, also, if the
*** - job changed status, we keep track of the change
*** - (deletion) of the job if complete or killed
*** - notified if stopped
*/

void			process_jobs_option_p(t_job **job)
{
	if (job_is_stopped(*job) && (*job)->running != 0)
		(*job)->notified = 1;
	ft_dprintf(1, "[%d]\n", (*job)->pgid);
	if (job_is_completed(*job))
		free_job_after_signal(job);
}

/*
*** - Aim of the function :
*** - If the command is "jobs" or "jobs -l / -p"
*** - without any number specified
*** - In that case, we list all the jobs in bg
*/

void			process_jobs_only_arg(option)
{
	t_job	*job;

	job = getter_job()->first_job;
	while ((job = job->next))
	{
		if (job->state == -1 && job->sep == SPL_SPRLU)
		{
			if (option == 0)
				process_jobs_without_options(&job);
			else if (option == 'p')
				process_jobs_option_p(&job);
			else if (option == 'l')
				process_jobs_option_l(&job);
		}
	}
}

/*
*** - Aim of the function :
*** - Manage the jobs builtin
*** - We first check the usage, return 2 if problem
*** - Then, if no specific number has been specified
*** - (jobs %1 for example), we list all the jobs in bg
*** - if a number has been specified, we show the info for that
*** - specific job if it exists, otherwise print an error
*/

int				ft_builtin_jobs(char **cmd)
{
	int		begin;
	char	option;
	int		len;
	BOOL	other_arg;
	t_job	**job;

	job = NULL;
	len = ft_len_array_char(cmd);
	if (ft_normalize_av(&cmd, &option, &begin, &other_arg))
		return (2);
	if (other_arg == 0)
		process_jobs_only_arg(option);
	else
	{
		while (++begin < len)
		{
			if (option == 0 && find_jobnum(cmd[begin], job))
				process_jobs_without_options(job);
			else if (option == 'p' && find_jobnum(cmd[begin], job))
				process_jobs_option_p(job);
			else if (option == 'l' && find_jobnum(cmd[begin], job))
				process_jobs_option_l(job);
			else
				ft_dprintf(1, "No such job %s\n", cmd[begin]);
		}
	}
	return (0);
}
