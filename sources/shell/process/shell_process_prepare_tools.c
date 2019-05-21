/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_prepare_tools.c                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/04 21:35:56 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 21:35:58 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	shell_clean_emptyargs(t_cmd *elem)
{
	char	**args2;
	int		i;
	int		n;

	args2 = (char **)malloc(sizeof(char *) * (ft_arrlen(elem->args) + 1));
	i = 0;
	n = 0;
	while (elem->args && elem->args[i])
	{
		if (ft_strlen(elem->args[i]))
			args2[n++] = ft_strdup(elem->args[i]);
		i++;
	}
	args2[n] = NULL;
	ft_arrdel(&elem->args);
	elem->args = args2;
}

void	check_hash_then_path(t_cmd *elem, t_shell *shell)
{
	char	*tmp;
	char	**all_env;

	tmp = NULL;
	if (shell->t)
		tmp = search_element(shell->t, elem->args[0]);
	if (tmp)
		elem->exec = ft_strdup(tmp);
	all_env = ft_arrjoin(shell->envl, shell->envp);
	if (!elem->exec)
		elem->exec = shell_getpathexec(elem->args[0], all_env);
	ft_arrdel(&all_env);
}
