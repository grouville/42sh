/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_export.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 17:33:02 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 17:33:02 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int         ft_usage_error(char *cmd, int ret)
{
    ft_dprintf(2, "%s\n", cmd);
    return (ret);
}

/*
*** - Aim of the function :
*** - Returns the len of the char **
*/

int		ft_len_array_char(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

/*
*** - Aim of the function : checks if the av is correct
*** - Then : keeps the letter of the last option set (*begin)
*** - Also :
*** - Keeps the position of the av I need to start looping on
*** - If jobs is the only arg, we return the position 1, in order to
*** - process the < process_jobs_alone > function
*** - Otherwise, we return the i - 1 in order to loop on the jobs
*/

static int		ft_normalize_av(char ***av, char *c, int *begin,
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
			return (ft_usage_error(
                "jobs: usage: jobs [-lp] [jobspec ...]", 1));
	}
    *begin = i - 1;
	return (0);
}

// -----------------------------------------------------------------------

void            process_jobs_without_options(t_job *job)
{
    if (job_is_completed(job))
    {
        if (job_is_signaled(job))
            format_job_info_signal(job, "Killed:", job->num);
        else
            format_job_info(job, "Done", job->num);
    }
    else if (job_is_stopped (job) && job->running != 0)
    {
			format_job_info(job, "Stopped", job->num);
			job->notified = 1;
	}
    else
            format_job_info(job, "Running", job->num);
}

void            process_jobs_option_p(t_job *job)
{
	if (job_is_stopped(job) && job->running != 0)
		job->notified = 1;
    ft_dprintf(1, "[%d]\n", job->pgid);
}

void		output_sig(int sig, char **signal_output)
{
    if (sig == 21)
        *signal_output = ft_strdup("(tty output):");
    else if (sig == 22)
        *signal_output = ft_strdup("(tty input):");
    else
        *signal_output = ft_strdup("Error unknown:");
}

void 		format_job_info_signal_l_option(t_job *j,
				const char *status, int sig)
{
	int 	i;
	t_cmd	*elem;
	int		job_pos;
    char    *signal_output;

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
** Format information about job status for the user to look at.
*/

void	format_job_info_l_option(t_job *j, const char *status)
{
	int		i;
	int		job_pos;
	t_cmd	*elem;
	char 	**args;

	ft_dprintf(1, "[%d]+ %d %-10s", j->num, j->pgid, status);
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

void            process_jobs_option_l(t_job *job)
{
    if (job_is_completed(job))
    {
        if (job_is_signaled(job))
            format_job_info_l_option(job, "Killed:");
        else
            format_job_info_l_option(job, "Done");
    }
    else if (job_is_stopped (job) && job->running != 0)
    {
		format_job_info_signal_l_option(job, "Stopped", job->running);
		job->notified = 1;
	}
    else
        format_job_info_l_option(job, "Running");
}

void            process_jobs_only_arg(option)
{
    t_job *job;

    job = getter_job()->first_job;
    while ((job = job->next))
    {
        if (job->state == -1 && job->sep == SPL_SPRLU)
        {
            if (option == 0)
                process_jobs_without_options(job);
            else if (option == 'p')
                process_jobs_option_p(job);
            else if (option == 'l')
                process_jobs_option_l(job);
            // printf("job->num: |%d| - notified: |%d|%s\n", job->num, job->state, job->cmds->args[0]);
        }
    }
}

// une fois passe dans jobs, ne pas afficher le resultat de do_job_modif
// ==> Si arg[0] == job, pas de job notification, modifier la fonction, ajouter la condition

t_job   *find_jobnum(char *num)
{
    t_job  *job;
	int number;

	if (*num == '%')
		number = ft_atoi(num + 1);	
	else if (ft_isdigit(*num))
		number = ft_atoi(num);
	else
		return (NULL);
    job = getter_job()->first_job;
    while ((job = job->next))
        if (job->num == number && job->sep == SPL_SPRLU)
            break ;
    return (job);
}

int			    ft_builtin_jobs(char **cmd)
{
    int     begin;
    char    option;
    int     len;
    BOOL    other_arg;

    len = ft_len_array_char(cmd);
    if (ft_normalize_av(&cmd, &option, &begin, &other_arg))
        return (2);
    // process when no other argument than -l -p or nothing
    if (other_arg == 0)
        process_jobs_only_arg(option);
    // process with jobs id, loop on them
    else
    {
        while (++begin < len)
        {
            if (option == 0 && find_jobnum(cmd[begin]))
                process_jobs_without_options(find_jobnum(cmd[begin]));
            else if (option == 'p' && find_jobnum(cmd[begin]))
                process_jobs_option_p(find_jobnum(cmd[begin]));
            else if (option == 'l' && find_jobnum(cmd[begin]))
                process_jobs_option_l(find_jobnum(cmd[begin]));
            else
                ft_dprintf(1, "No such job %s\n", cmd[begin]);
        }
    }
    return (0);
}

// A FAIRE : remplacer l'affichage quand jobs est lancé ; ne pas faire do job notification
// Aussi, ne pas oublier que fonction format_info_signal has been corrected
// Checker retour -> quand job n'est pas trouvé