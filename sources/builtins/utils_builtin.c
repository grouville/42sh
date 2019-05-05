/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/23 13:13:48 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 23:18:52 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
*** - Aim of the function :
*** - Returns true if command is builtin
*/

BOOL			shell_is_builtin(t_cmd *elem, t_shell *shell)
{
	int i;

	if (!elem->args)
		return (0);
	if (elem->args[0] && builtin_localvar(&elem->args, elem->args_raw))
	{
		i = 0;
		while (elem->args[i])
			builtin_env_add(&shell->envp, &shell->envl, elem->args[i++]);
		ft_arrdel(&elem->args);
		return (1);
	}
	else if (elem->args[0] && (ft_strcmp("hash", elem->args[0]) == 0 ||
	!ft_strcmp("echo", elem->args[0]) || !ft_strcmp("cd", elem->args[0]) ||
	!ft_strcmp("set", elem->args[0]) || !ft_strcmp("unset", elem->args[0]) ||
	!ft_strcmp("export", elem->args[0]) || !ft_strcmp("type", elem->args[0]) ||
	!ft_strcmp("alias", elem->args[0]) || !ft_strcmp("fc", elem->args[0]) ||
	!ft_strcmp("unalias", elem->args[0]) || !ft_strcmp("test", elem->args[0]) ||
	!ft_strcmp("fg", elem->args[0]) || !ft_strcmp("bg", elem->args[0]) ||
	!ft_strcmp("jobs", elem->args[0]) ||
	!ft_strcmp("exit", elem->args[0])) && (elem->done = 1))
		return (1);
	else
		return (0);
}

BOOL			shell_is_builtin_str(char *str)
{
	if (!str)
		return (1);
	else if ((ft_strcmp("hash", str) == 0 ||
	!ft_strcmp("echo", str) || !ft_strcmp("cd", str) ||
	!ft_strcmp("set", str) || !ft_strcmp("unset", str) ||
	!ft_strcmp("export", str) || !ft_strcmp("type", str) ||
	!ft_strcmp("alias", str) || !ft_strcmp("fc", str) ||
	!ft_strcmp("unalias", str) || !ft_strcmp("test", str) ||
	!ft_strcmp("fg", str) || !ft_strcmp("bg", str) ||
	!ft_strcmp("jobs", str) ||
	!ft_strcmp("exit", str)))
		return (1);
	else
		return (0);
}

/*
*** - Aim of the function
*** - Check if arg is a number
*/

int				is_number(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

/*
*** - Aim of the function :
*** - Jobs Builtin -> check usage jobs
*** - checks if the av is correct
*** - Then : keeps the letter of the last option set (*begin)
*** - Also :
*** - Keeps the position of the av I need to start looping on
*** - If jobs is the only arg, we return the position 1, in order to
*** - process the < process_jobs_alone > function
*** - Otherwise, we return the i - 1 in order to loop on the jobs
*/

int				ft_normalize_av(char ***av, char *c, int *begin,
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
