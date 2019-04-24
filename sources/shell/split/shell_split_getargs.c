/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_split_getarg.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 18:55:09 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 18:55:09 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** Calcul la longueur de l'argument
** Les conditions de fin sont :
**  - match de nouveau le charactere de {quote}
**  - match avec {;} OU {&&} OU {|}
*/

size_t	len_arg(char *str, char quote)
{
	int i;

	i = (quote == ' ') ? 0 : 1;
	while (str && str[i])
	{
		if (str[i] == '\\' && ft_strlen(str) >= (i + 2) && quote != '\'')
			i += 2;
		if (ft_strchr("'\"", str[i]) && quote == ' ')
			quote = str[i++];
		else if (str[i] == quote && quote != ' ')
		{
			quote = ' ';
			i++;
		}
		else if ((quote == ' ' && (ft_strchr(";|", str[i]))) || (str[i] == '&'
					&& str[i + 1] == '\0') || (str[i] == quote &&
					(quote == ' ' || ft_strchr("\0 ", str[i + 1]))))
			break ;
		else
			i += (str[i]) ? 1 : 0;
	}
	return ((size_t)i);
}

int		get_nbarg(char *str, t_prompt *prompt)
{
	char	quote;
	int		nb_args;
	size_t	lenarg;

	str = shell_trim(&str);
	nb_args = 0;
	while (*str)
	{
		str = shell_trim(&str);
		quote = ft_strchr("'\"", str[0]) ? str[0] : (char)' ';
		lenarg = len_arg(str, quote);
		if (ft_strlen(str) && lenarg == 0)
			*prompt = B_QUOTE;
		str += lenarg;
		if (lenarg == 0 && !ft_strchr(";|&", str[0]))
			return (0);
		nb_args += 1;
		str = shell_trim(&str);
		if (ft_strchr(";|&", str[0]))
			break ;
	}
	return (nb_args);
}

/*
** subtitue le premier {args_tab} de {str} et avance de {len} de {args_tab}.
** {arg} garde les quotes pour {shell_envsub} au moment du [process].
*/

char	*get_arg(char **str, t_cmd *cmd)
{
	unsigned int	i;
	char			quote;
	char			*arg;

	i = 0;
	while (*str && ft_isspace((*str)[i]))
		i++;
	if (!(*str) || (*str)[i] == '\0')
		return (NULL);
	quote = ft_strchr("'\"", (*str)[i]) ? (*str)[i] : (char)' ';
	arg = ft_strsub(*str, i, len_arg(*str + i, quote));
	cmd->output = shell_std_out(&arg, &cmd->output, quote);
	shell_std_in(&arg, quote, cmd);
	*str = *str + i + len_arg(*str + i, quote);
	return (arg);
}

t_cmd	*get_args(char **line, char **envp, t_prompt *prompt)
{
	int		i;
	int		nb_arg;
	t_cmd	*cmd;

	if (!(*line) || (*line)[0] == '\0' || !(nb_arg = get_nbarg(*line, prompt)))
		return (NULL);
	cmd = (t_cmd *)shl_mlc("cmd", 3, &line, envp, sizeof(t_cmd));
	cmd->args = (char **)malloc(sizeof(char *) * (nb_arg + 1));
	cmd->args[nb_arg] = NULL;
	cmd->output = NULL;
	cmd->input = NULL;
	cmd->hrdc = NULL;
	cmd->exec = NULL;
	cmd->signal = 0;
	cmd->ret = 0;
	cmd->process.fd_stdin = ft_strdup("&0");
	cmd->process.fd_stdout = ft_strdup("&1");
	cmd->process.fd_stderr = ft_strdup("&2");
	cmd->process.stdin_send = NULL;
	cmd->process.fd_fileout = 0;
	cmd->process.fd_fileerr = 0;
	i = 0;
	while (i < nb_arg)
		cmd->args[i++] = get_arg(line, cmd);
	return (cmd);
}
