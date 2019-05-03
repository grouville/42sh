/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_export.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 17:33:02 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 00:42:45 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
*** - Aim of the function :
*** - Print the usage error
*/

int			ft_usage_error(char *cmd, int ret)
{
	ft_dprintf(2, "%s\n", cmd);
	return (ret);
}

/*
*** - Aim of the function :
*** - Returns the len of the char **
*/

int			ft_len_array_char(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

/*
*** - Aim of the function :
*** - Free job function for the jobs builtin
*/

void		free_job_builtin_job(t_job **j)
{
	clean_cmd(&(*j)->cmds);
	free(*j);
	*j = NULL;
}

/*
*** - Aim of the function :
*** - Free job function for the jobs builtin
*** - Find the current job
*** - link the previous job to the next
*** - free the current job
*** - assign the current job to the previous one
*** - And voilà
*/

void		free_job_after_signal(t_job **job)
{
	t_job	*jprev;
	t_job	*jnext;

	jprev = getter_job()->first_job;
	while (jprev)
	{
		if (jprev->next->pgid == (*job)->pgid)
			break ;
		jprev = jprev->next;
	}
	jnext = (*job)->next;
	jprev->next = jnext;
	free_job_builtin_job(job);
	*job = jprev;
}

/*
*** - Aim of the function :
*** - Find the corresponding job according to the job num
*** - specified. Then, returns it and assign it to the j variable
*/

t_job		*find_jobnum(char *num, t_job **j)
{
	t_job	*job;
	int		number;

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
	*j = job;
	printf("jobnum: %d|%s|\n", (*j)->num, (*j)->cmds->args[0]);
	return (job);
}
