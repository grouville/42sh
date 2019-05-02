/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_jobs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 08:00:35 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 08:01:32 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int				ft_usage_error(char *cmd, int ret)
{
	ft_dprintf(2, "%s\n", cmd);
	return (ret);
}

/*
*** - Aim of the function :
*** - Returns the len of the char **
*/

int				ft_len_array_char(char **av)
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

static int		ft_normalize_av(char ***av, char *c, int *begin, BOOL *other_arg)
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
			return (ft_usage_error("jobs: usage: jobs [-lp] [jobspec ...]", 1));
	}
	*begin = i - 1;
	return (0);
}

void			process_jobs_alone(option)
{
	// if (option == 0)
	//     process_jobs_without_options(NULL);
	// else if (option == 'p')
	//     process_jobs_option_p(NULL);
	// else if (option == 'l')
	//     process_jobs_option_l(NULL);
}

// une fois passe dans jobs, ne pas afficher le resultat de do_job_modif
// ==> Si arg[0] == job, pas de job notification, modifier la fonction, ajouter la condition

int				ft_builtin_jobs(char **cmd)
{
	int		begin;
	char	option;
	int		len;
	BOOL	other_arg;

	len = ft_len_array_char(cmd);
	if (ft_normalize_av(&cmd, &option, &begin, &other_arg))
		return (2);
	// process when no other argument than -l -p or nothing
	if (other_arg == 0)
		process_jobs_alone(option);
	// process with jobs id, loop on them
	else
	{
		while (++begin < len)
		{
			// if (option == 0)
			//     process_jobs_without_options(cmd[begin]);
			// else if (option == 'p')
			//     process_jobs_option_p(cmd[begin]);
			// else if (option == 'l')
			//     process_jobs_option_l(cmd[begin]);
		}
	}
	return (0);
}
