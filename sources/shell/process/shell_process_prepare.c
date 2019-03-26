/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_prepare.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/12 01:08:34 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/12 01:08:34 by ythollet    ###    #+. /#+    ###.fr     */
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
	char *tmp;

	tmp = NULL;
	if (shell->t)
		tmp = search_element(shell->t, elem->args[0]);
	if (tmp)
		elem->exec = ft_strdup(tmp);
	if (!elem->exec)
		elem->exec = shell_getpathexec(elem->args[0], shell->envp);
}


void	shell_prepare_args(t_cmd *elem, t_shell *shell)
{
	int i;

	i = 0;
	while (elem->args && elem->args[i])
	{
		shell_envpsub(&elem->args[i], shell->envp, shell->envl);
		shl_quotesub(elem->args[i]);
		if (i == 0)
		{
			check_hash_then_path(elem, shell);
			if (!elem->exec)
				elem->exec = ft_strdup("not found");
			else if ((int)elem->exec == -1)
				elem->exec = ft_strdup("directory");
			else if ((int)elem->exec == -2)
				elem->exec = ft_strdup("file or directory");
			else if ((int)elem->exec == -3)
				elem->exec = ft_strdup("no allowed");
		}
		i++;
	}
}

/*
** Clean des arg vide et get exec path et clean les inputs à -1 de HRDC
*/

void	shell_prepare(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*elem;

	elem = cmd;
	while ((elem = elem->next_cmd))
	{
		shell_clean_emptyargs(elem);
		shell_prepare_args(elem, shell);
	}
}
