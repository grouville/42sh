/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_split_stdin_tools.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 00:03:34 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/02 00:03:34 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	complete_stdin(char **arg, char quote, char **std_in)
{
	int		last;
	int		len;

	last = 0;
	len = 0;
	while (std_in && std_in[last] != NULL)
		last++;
	if (std_in && (int)std_in[last - 1] == -2 && len_stdin(*arg, quote) > 0)
	{
		len = len_stdin(*arg, quote);
		std_in[last - 1] = ft_strcutword(arg, 0, len);
	}
}

void	complete_all_stdin(char **arg, char quote, t_cmd *cmd)
{
	int		len;
	char	*tmp;

	complete_stdin(arg, quote, cmd->hrdc);
	complete_stdin(arg, quote, cmd->input);
	if (cmd->process.stdin_send && (int)cmd->process.stdin_send == -2)
	{
		len = len_stdin(*arg, quote);
		tmp = ft_strcutword(arg, 0, len);
		cmd->process.stdin_send = ft_strjoin(tmp, "\n");
		ft_strdel(&tmp);
	}
}

int		len_stdin(char *str, char quote)
{
	int i;

	i = (quote == ' ') ? 0 : 1;
	while (str && str[i])
	{
		if (str[i] == '\\' && ft_strlen(str) >= (i + 2) && quote != '\'')
			i += 2;
		if (ft_strchr("'\"", str[i]) && quote == ' ')
			quote = str[i];
		else if (str[i] == quote && quote != ' ')
			quote = ' ';
		if (quote == ' ' && ft_strchr("><", str[i]))
			break ;
		if (str[i] == quote && (quote == ' ' || ft_strchr("\0 ", str[i + 1])))
			break ;
		i += (str[i] ? 1 : 0);
	}
	return (i);
}

int		shell_stdin_sub(char **arg, int i, char ***std_in)
{
	int		last;
	char	quote;
	int		len;

	last = 0;
	while ((*std_in)[last] != NULL)
		last++;
	if ((*arg)[i] == '\0')
	{
		(*std_in)[last - 1] = (char *)-2;
		return (i);
	}
	quote = ft_strchr("\"'", **arg) ? **arg : (char)' ';
	len = len_stdin(*arg + i, quote);
	if (len > 0)
		(*std_in)[last - 1] = ft_strsub(*arg, (unsigned)i, (size_t)len);
	return (i + len);
}
