/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_exec.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 22:44:23 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/21 22:44:23 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	shell_child(t_cmd *elem, t_shell *shell)
{
	execve(elem->exec, elem->args, shell->envp);
	exit(EXIT_SUCCESS);
}

int		shell_father(int pid_child)
{
	wait(&pid_child);
	return (WEXITSTATUS(pid_child));
}

/*
** On retourne 0 si RAS ou 1 si execve fail
*/

void	shell_execve(t_cmd *elem, t_shell *shell)
{
	int	child;

	if ((child = fork()) == 0)
		shell_child(elem, shell);
	else
		elem->ret = shell_father(child);
}
