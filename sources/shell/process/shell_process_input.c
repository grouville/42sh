/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_input.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 15:03:02 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/21 15:03:02 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		check_fd_input(char *input, t_shell *shell)
{
	int fd;
	int i;

	if ((int)input != -3 && (int)input != -1 && input[0] == '&')
	{
		shell_envpsub(&input, shell->envp, shell->envl);
		shl_quotesub(input);
		i = 1;
		while (ft_isdigit(input[i]))
			i++;
		if (input[i] != '\0')
			return (shell_error_prepare("ambiguous", input) - 1);
		fd = ft_atoi(input + 1);
		if (fd < 0 || fd > 2)
			return (shell_error_prepare("bad fd", input) - 1);
		else
			return (1);
	}
	return (0);
}

void	complete_stdin_path(char **std_in, t_shell *shell)
{
	char *tmp;
	char *cur_dir;

	shell_envpsub(std_in, shell->envp, shell->envl);
	shl_quotesub(*std_in);
	if ((*std_in)[0] != '/')
	{
		tmp = *std_in;
		cur_dir = get_cur_dir();
		*std_in = ft_strjoin_mltp(3, cur_dir, "/", *std_in);
		ft_strdel(&cur_dir);
		ft_strdel(&tmp);
	}
}

int		check_input_file(char **std_in, t_shell *shell)
{
	char *msg_err;

	if ((int)*std_in != -3 && (int)*std_in != -1)
	{
		msg_err = ft_strdup(*std_in);
		complete_stdin_path(std_in, shell);
		if (access(*std_in, F_OK) == -1)
			return (shell_error_prepare("not found", msg_err));
		else if (ft_isdir(*std_in))
			return (shell_error_prepare("Is directory", msg_err));
		else if (access(*std_in, R_OK) == -1)
			return (shell_error_prepare("denied", msg_err));
		ft_strdel(&msg_err);
	}
	return (1);
}

/*
** Même si c'est seulement le dernier input qui est lu ont les check tous.
** On remplit stdin_send seulement si c'est le dernier input et qu'il
** ne correspond pas à un HRDC
*/



int		shell_read_input(t_cmd *elem, t_shell *shell)
{
	int		i;
	int		is_fd;
	int		fd;
	char	*tmp;

	i = 0;
	while (elem->input && elem->input[i])
	{
		if ((is_fd = check_fd_input(elem->input[i], shell)) == 1)
		{
			if (i == ft_arrlen(elem->input) - 1)
			{
				ft_strdel(&(elem->process).fd_stdin);
				(elem->process).fd_stdin = ft_strdup(elem->input[i]);
			}
		}
		else if (!is_fd && check_input_file(&elem->input[i], shell))
		{
			if (i == ft_arrlen(elem->input) - 1 && (int)elem->input[i] != -3
					&& (int)elem->input[i] != -1)
			{
				if ((fd = open(elem->input[i], O_RDONLY)) == -1)
					return (0);
				tmp = ft_itoa(fd);
				ft_strdel(&(elem->process).fd_stdin);
				(elem->process).fd_stdin = ft_strjoin("&", tmp);
				ft_strdel(&tmp);
			}
		}
		else
			return (0);
		i++;
	}
	return (1);
}
