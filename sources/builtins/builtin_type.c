/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_type.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 18:21:28 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/22 15:47:45 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	builtin_type_free(t_type *tp)
{
	int		i;

	i = 0;
	while (tp->bin[i])
		ft_strdel(&(tp->bin)[i++]);
	ft_strdel(&tp->bin[i]);
	ft_strdel(&tp->op);
	free(tp->bin);
	free(tp);
}

int		builtin_type_init(t_type **tp, char **envp, char **args)
{
	if (!(*tp = (t_type*)malloc(sizeof(t_type))))
		exit(EXIT_FAILURE);
	(*tp)->op = NULL;
	if (((*tp)->i =
	builtin_get_options(&(*tp)->op, args, "aptP") - 1) == -2)
	{
		ft_dprintf(2, "42sh: type: -%s: invalid option\ntype: usage: type"
				"[-afptP] name [name ...]\n", (*tp)->op);
		ft_strdel(&(*tp)->op);
		free(*tp);
		return (1);
	}
	(*tp)->b_path = get_envp(envp, "PATH");
	(*tp)->bin = ft_strsplit((*tp)->b_path, ':');
	(*tp)->match[1] = 0;
	return (0);
}

void	builtin_type_search_bin(t_type *tp, char **args)
{
	DIR				*dir;
	struct dirent	*dirent;

	tp->match[0] = 0;
	while (tp->bin && tp->bin[++tp->j])
	{
		if ((dir = opendir(tp->bin[tp->j])))
		{
			while ((dirent = readdir(dir)))
				if (!ft_strcmp(dirent->d_name, args[tp->i]))
				{
					builtin_type_display(
							dirent->d_name, tp->bin[tp->j], tp->op, 1);
					tp->match[0] = 1;
					break ;
				}
			closedir(dir);
		}
		if (tp->match[0])
			break ;
	}
}

int		builtin_type(char **args, char **envp)
{
	t_type *tp;

	if (builtin_type_init(&tp, envp, args) == 1)
		return (1);
	while (args[++tp->i] && (tp->j = -1) == -1)
	{
		if (((!tp->op || (ft_strchr(tp->op, 'a') && !ft_strchr(tp->op, 'p')
		&& !ft_strchr(tp->op, 'P')) || (ft_strchr(tp->op, 't') &&
		!ft_strchr(tp->op, 'P') && !ft_strchr(tp->op, 'p'))) &&
		builtin_type_check_builtin(args[tp->i])))
		{
			builtin_type_display(args[tp->i], NULL, tp->op, 0);
			if (!tp->op)
				continue ;
		}
		((args[tp->i][0] == '/' || (args[tp->i][0] == '.' && args[tp->i][1] ==
		'/')) && !access(args[tp->i], F_OK) && check_executable_file(args
		[tp->i]) && (tp->match[0] = 1)) ? builtin_type_display(args[tp->i],
				NULL, tp->op, 1) : builtin_type_search_bin(tp, args);
		if (!tp->match[0] && !builtin_type_check_builtin(args[tp->i])
		&& (tp->match[1] = 1))
			ft_dprintf(2, "42sh: type: %s: not found\n", args[tp->i]);
	}
	builtin_type_free(tp);
	return (tp->match[1]);
}
