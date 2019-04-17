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
** On retourne 0 si EXIT_SUCCESS ou 1 si EXIT_FAILED
*/

void	shell_execve(t_cmd *elem, t_shell *shell)
{
	int	child;

	if ((child = fork()) == 0)
		shell_child(elem, shell);
	else
		elem->ret = shell_father(child);
}

int		shell_exec_error(int is_builtin, t_cmd *elem)
{
	int ret;

	ret = 1;
	if (!is_builtin && elem->exec)
	{
		if (ft_strcmp("not found", elem->exec) == 0)
			ft_dprintf(2, "42sh: %s: command not found\n", elem->args[0]);
		else if (ft_strcmp("directory", elem->exec) == 0)
			ft_dprintf(2, "42sh: %s: Is a directory\n", elem->args[0]);
		else if (ft_strcmp("file or directory", elem->exec) == 0)
			ft_dprintf(2, "42sh: %s: No such file or directory\n",
					   elem->args[0]);
		else if (ft_strcmp("no allowed", elem->exec) == 0)
			ft_dprintf(2, "42sh: %s: Permission denied\n", elem->args[0]);
		else
			ret = 0;
		if (ft_strcmp("no allowed", elem->exec) == 0 ||
			ft_strcmp("directory", elem->exec) == 0)
			elem->ret = 126;
		else if (ft_strcmp("file or directory", elem->exec) == 0 ||
				 ft_strcmp("not found", elem->exec) == 0)
			elem->ret = 127;
	}
	return (ret);
}

/*
** ATTENTION : shell_exec est dans un fork donc ne pas modif envp & envl
** return :
**   0 --> ok elem suivant
**   1 --> elem fail
**  -1 --> un exit est nécessaire
*/

int		shell_exec(t_cmd *elem, t_shell *shell)
{
	int	is_builtin;

	if (!shell_read_input(elem, shell) || !shell_set_output(elem, shell))
		return (1);
	shell_plomberie(elem->process);
	is_builtin = shell_builtin(elem, shell);
	if (!shell_exec_error(is_builtin, elem) && !is_builtin && elem->exec)
		shell_execve(elem, shell);
	else if (is_builtin == -1)
		return (-1);
	if (elem->process.fd_stdin[1] != '0')
		close(ft_atoi(elem->process.fd_stdin + 1));
	if (elem->process.fd_stdout[1] != '1')
		close(ft_atoi(elem->process.fd_stdout + 1));
	if (elem->process.fd_stderr[1] != '2')
		close(ft_atoi(elem->process.fd_stderr + 1));
	return (elem->ret);
}
