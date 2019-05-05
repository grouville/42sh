/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_output.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 15:02:55 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/21 15:02:55 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		check_fd_output(char **ptn_output, t_shell *shell)
{
	int		fd;
	int		i;
	char	*output;

	fd = 0;
	output = *ptn_output;
	if (output[0] == '&')
	{
		shell_envpsub(ptn_output, shell->envp, shell->envl);
		shl_quotesub(output);
		if (ft_strcmp(*ptn_output, "&-") == 0)
			return (1);
		i = 1;
		while (ft_isdigit(output[i]))
			i++;
		if (output[i] != '\0')
			return (shell_error_prepare("ambiguous", output) - 1);
		else if (output[i] == '\0')
			fd = ft_atoi(output + 1);
		if ((fd < 0 || fd > 2))
			return (shell_error_prepare("bad fd", output) - 1);
		else
			return (1);
	}
	return (0);
}

int		is_recheable_output(t_output *output, t_shell *shell)
{
	int		fd_open;
	char	*msg_err;

	msg_err = ft_strdup(output->to);
	complete_output_paths(&output->to, shell);
	if (output->append)
		fd_open = open(output->to, O_WRONLY | O_CREAT | O_APPEND,
							S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	else
		fd_open = open(output->to, O_WRONLY | O_CREAT | O_TRUNC,
							S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd_open < 0)
	{
		if (ft_isdir(output->to))
			return (shell_error_prepare("Is directory", msg_err));
		else if (!path_to_output_exist(output->to))
			return (shell_error_prepare("not found", msg_err));
		else if (path_to_output_recheable(output->to) == -1)
			return (shell_error_prepare("pathdenied", msg_err));
		else if (access(output->to, F_OK) == 0 &&
					access(output->to, W_OK) == -1)
			return (shell_error_prepare("denied", msg_err));
	}
	ft_strdel(&msg_err);
	return (fd_open);
}

void	shell_set_output_file(t_output *output, t_cmd *elem, int fd_file)
{
	if (output->from == 1)
	{
		(elem->process).fd_stdout = ft_strdup(output->to);
		(elem->process).fd_fileout = fd_file;
	}
	else if (output->from == 2)
	{
		(elem->process).fd_stderr = ft_strdup(output->to);
		(elem->process).fd_fileerr = fd_file;
	}
}

void	shell_set_output_fd(t_output *output, t_cmd *elem)
{
	if (ft_atoi(output->to + 1) == 1 && output->from == 0)
		(elem->process).fd_stdin = ft_strdup((elem->process).fd_stdout);
	else if (ft_atoi(output->to + 1) == 1 && output->from == 1)
	{
		(elem->process).fd_stdout = ft_strdup((elem->process).fd_stdout);
		(elem->process).fd_fileout = (elem->process).fd_fileout;
	}
	else if (ft_atoi(output->to + 1) == 1 && output->from == 2)
	{
		(elem->process).fd_stderr = ft_strdup((elem->process).fd_stdout);
		(elem->process).fd_fileerr = (elem->process).fd_fileout;
	}
	if (ft_atoi(output->to + 1) == 2 && output->from == 0)
		(elem->process).fd_stdin = ft_strdup((elem->process).fd_stderr);
	else if (ft_atoi(output->to + 1) == 2 && output->from == 1)
	{
		(elem->process).fd_stdout = ft_strdup((elem->process).fd_stderr);
		(elem->process).fd_fileout = (elem->process).fd_fileerr;
	}
	else if (ft_atoi(output->to + 1) == 2 && output->from == 2)
	{
		(elem->process).fd_stderr = ft_strdup((elem->process).fd_stderr);
		(elem->process).fd_fileerr = (elem->process).fd_fileerr;
	}
	shell_set_fd_null(output, elem);
}

/*
** Création de file out, return 0 si erreur (no right..)
*/

int		shell_set_output(t_cmd *elem, t_shell *shell)
{
	t_output	*output;
	int			is_fd;
	int			fd_file;
	char 		*tmp;

	fd_file = -1;
	output = elem->output;
	while (output != NULL)
	{
		tmp = NULL;
		if (output->from == 1 && (elem->process.last_redi = 1))
		{
			tmp = (elem->process).fd_stdout;
			if (elem->process.fd_fileout == fd_file)
				close(fd_file);
		}
		else if (output->from == 2 && (elem->process.last_redi = 2))
		{
			tmp = (elem->process).fd_stderr;
			if (elem->process.fd_fileerr == fd_file)
				close(fd_file);
		}
		if (((is_fd = check_fd_output(&output->to, shell)) == 1))
			shell_set_output_fd(output, elem);
		else if (!is_fd && (fd_file = is_recheable_output(output, shell)))
			shell_set_output_file(output, elem, fd_file);
		else
			return (0);
		ft_strdel(&tmp);
		output = output->next;
	}
	return (1);
}
