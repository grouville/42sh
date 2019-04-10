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

int		shell_prepare_args(t_cmd *elem, t_shell *shell)
{
	int i;

	i = 0;
	while (elem->args && elem->args[i])
	{
		if (!shell_envpsub(&elem->args[i], shell->envp, shell->envl))
			return (0);
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
	return (1);
}

t_job	*shell_prepare_jobs(t_cmd *cmd)
{
	t_job	*jobs;
	t_job	*job_nxt;
	t_cmd	*elem;
	int 	i;

	jobs = (t_job *)malloc(sizeof(t_job));
	job_nxt = jobs;
	elem = cmd;
	while ((elem = elem->next_cmd))
	{
		job_nxt->next = (t_job *)malloc(sizeof(t_job));
		job_nxt = job_nxt->next;
		job_nxt->cmds = elem;
		while (elem->sep && elem->sep != PTN_VRGL && elem->sep != SPL_SPRLU)
			elem = elem->next_cmd;
		job_nxt->sep = elem->sep;
		elem->sep = 0;
	}
	job_nxt->next = NULL;
	return (jobs);
}

/*
** Clean des arg vide et get exec path
** elem->process.stdin_send à NULL est une protection d'un seg
*/

t_job	*shell_prepare(t_cmd *cmd)
{
	t_cmd	*elem;
	t_job	*jobs;

	signal(SIGINT, shell_prcs_sigint);
	elem = cmd;
	while ((elem = elem->next_cmd))
	{
		elem->args_raw = ft_arrdup(elem->args);
		shell_clean_emptyargs(elem);
		if ((int)elem->process.stdin_send == -1 ||
			(int)elem->process.stdin_send == -2)
			elem->process.stdin_send = NULL;
	}
	jobs = shell_prepare_jobs(cmd);
	return (jobs);
}
