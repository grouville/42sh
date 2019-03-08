/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_output_tools.c                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 23:11:59 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/21 23:11:59 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	shell_set_fd_null(t_output *output, t_cmd *elem)
{
	int		devnull;
	char	*tmp;

	if (ft_strcmp((elem->output)->to, "&-") == 0)
	{
		devnull = open("/dev/null", O_WRONLY);
		tmp = ft_itoa(devnull);
		if (output->from == 1)
			elem->process.fd_stdout = ft_strjoin("&", tmp);
		if (output->from == 2)
			elem->process.fd_stderr = ft_strjoin("&", tmp);
		ft_strdel(&tmp);
	}
}

int		path_to_output_exist(char *output)
{
	int i;
	int exist;

	i = ft_strlen(output);
	while (i > 0)
	{
		if (output[i] == '/')
		{
			output[i] = '\0';
			break ;
		}
		i--;
	}
	exist = ft_isdir(output);
	output[i] = '/';
	return (exist);
}

int		path_to_output_recheable(char *output)
{
	int	i;
	int recheable;

	i = ft_strlen(output);
	while (i > 0)
	{
		if (output[i] == '/')
		{
			output[i] = '\0';
			break ;
		}
		i--;
	}
	recheable = access(output, W_OK);
	if (recheable == 0)
		output[i] = '/';
	return (recheable);
}

/*
** Ajoute le dossier courant
*/

int		complete_output_paths(char **output_to, t_shell *shell)
{
	char *tmp;
	char *cur_dir;

	shell_envpsub(output_to, shell->envp, shell->envl);
	shl_quotesub(*output_to);
	if ((*output_to)[0] != '/')
	{
		cur_dir = get_cur_dir();
		tmp = *output_to;
		*output_to = ft_strjoin_mltp(3, cur_dir, "/", *output_to);
		ft_strdel(&tmp);
		ft_strdel(&cur_dir);
	}
	return (1);
}
