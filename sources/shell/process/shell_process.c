/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/28 20:39:43 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/28 20:39:57 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
** ATTENTION shell->str peut etre vide apres un heredoc
*/

#include "shell.h"

int		shell_exec_error(int is_builtin, t_cmd *elem)
{
	if (!is_builtin && elem->exec &&
		ft_strcmp("not found", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: command not found\n", elem->args[0]);
	else if (!is_builtin && elem->exec &&
			 ft_strcmp("directory", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: Is a directory\n", elem->args[0]);
	else if (!is_builtin && elem->exec &&
				ft_strcmp("file or directory", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: No such file or directory\n", elem->args[0]);
	else if (!is_builtin && elem->exec &&
				ft_strcmp("no allowed", elem->exec) == 0)
		ft_dprintf(2, "42sh: %s: Permission denied\n", elem->args[0]);
	else
		return (0);
	elem->ret = 1;
	return (1);
}

/*
** return :
**   0 --> ok elem suivant
**   1 --> elem fail ou un séparateur stop l'execution des elem
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
	return (elem->ret);
}

/*
** elem->ret se prend -2 si builtin exit fail, on le corrige pour 1
** puis on rajoute elem->ret dans shell->envl
*/

void	shell_ret(t_cmd *elem, t_shell *shell)
{
	char *tmp;

	elem->ret = (elem->ret == -2) ? 1 : elem->ret;
	tmp = ft_itoa(elem->ret);
	if (!(check_replace_env_variable(&shell->envl, "?", tmp)))
		shell->envl = append_key_env(shell->envl, "?", tmp);
	ft_strdel(&tmp);
}

int		shell_process(t_cmd **cmd, t_shell *shell)
{
	t_cmd	*elem;
	int		fd[3];
	int		exec;

	shell_prepare(*cmd, shell);
	signal(SIGINT, shell_prcs_sigint);
	elem = *cmd;
	while (elem && (elem = elem->next_cmd))
	{
		read_lexing(elem);
		shell_save_fd(fd);
		if (elem->sep == SPL_PIPE)
			exec = shell_exec_pipes(&elem, shell);
		else
			exec = shell_exec(elem, shell);
		shell_reinit_fd(fd);
		shell_ret(elem, shell);
		if (exec == -1)
			return (-1);
		else if ((exec == EXIT_SUCCESS && elem->sep == DBL_PIPE) ||
			(exec > 0 && elem->sep == DBL_SPRLU))
			elem = elem->next_cmd;
	}
	shell_clean_data(cmd, shell, 1);
	return (1);
}


void	read_lexing(t_cmd *elem)
{
	t_output	*read;
	int 		i;

	ft_dprintf(2, "-------------\n");
	ft_dprintf(2, "Read exec : %s\n", elem->exec);
	i = 0;
	ft_dprintf(2, "Read array : ");
	while (elem->args && elem->args[i])
	{
		ft_dprintf(2, "arg[%i]=<%s> ", i, elem->args[i]);
		i++;
	}
	ft_dprintf(2, "\nRead output : ");
	read = elem->output;
	if (read == NULL)
		ft_dprintf(2, "(NULL)");
	while (read != NULL)
	{
		ft_dprintf(2, "from %d to <%s> append=%d - ", read->from, read->to, read->append);
		read = read->next;
	}

	ft_dprintf(2, "\nRead input : ");
	if (!elem->input)
		ft_dprintf(2, "(NULL)");
	i = 0;
	while (elem->input && (elem->input)[i] != NULL)
	{
		if ((int)(elem->input)[i] <= -1 && (int)(elem->input)[i] >= -3)
			ft_dprintf(2, "|%d| -", (int)(elem->input)[i++]);
		else
			ft_dprintf(2, "|%s| - ", (elem->input)[i++]);
	}
	ft_dprintf(2, "\nRead hrdc : ");
	if (!elem->hrdc)
		ft_dprintf(2, "(NULL)");
	i = 0;
	while (elem->hrdc && (elem->hrdc)[i] != NULL)
	{
		if ((int)(elem->hrdc)[i] <= -1 && (int)(elem->hrdc)[i] >= -3)
			ft_dprintf(2, "|%d| -", (int)(elem->hrdc)[i++]);
		else
			ft_dprintf(2, "|%s| - ", (elem->hrdc)[i++]);
	}
	if ((int)(elem->process).stdin_send == -1)
		ft_dprintf(2, "\nRead stdin : |%d|\n", (int)elem->process.stdin_send);
	else
		ft_dprintf(2, "\nRead stdin : |%s|\n", elem->process.stdin_send);
	ft_dprintf(2, "Read fd stdin : |%s|\n", elem->process.fd_stdin);
	ft_dprintf(2, "Read fd stdout : |%s|\n", elem->process.fd_stdout);
	ft_dprintf(2, "Read fileout : |%d|\n", elem->process.fd_fileout);
	ft_dprintf(2, "Read fd stderr : |%s|\n", elem->process.fd_stderr);
	ft_dprintf(2, "Read fileerr : |%d|\n", elem->process.fd_fileerr);
	ft_dprintf(2, "Et sep %d\n", elem->sep);
	ft_dprintf(2, "-------------\n");
}