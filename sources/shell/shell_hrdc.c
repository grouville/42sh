/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_hrdc_check.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 17:55:46 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:56:52 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** hrdc[i] prend la valeur de -3 pour indiqué d'être rempli
*/

int		del_next_hrdc(char **hrdc)
{
	int	i;

	i = 0;
	while (hrdc && (int)hrdc[i] == -3)
		i++;
	if (hrdc && hrdc[i])
	{
		ft_strdel(&hrdc[i]);
		hrdc[i] = (char *)-3;
	}
	return (1);
}

void	hrdc_match(t_prompt *prompt, t_cmd **cmd, t_shell *shell)
{
	int last;

	ft_strjoin_free(&shell->hrdc_tmp, shell->str);
	ft_strjoin_free(&shell->hrdc_tmp, "\n");
	del_next_hrdc((*cmd)->hrdc);
	if (get_next_hrdc((*cmd)->hrdc) == NULL)
	{
		*prompt = PROMPT;
		last = 0;
		while ((int)(*cmd)->input[last] != -1)
			last++;
		(*cmd)->input[last] = (char *)-3;
	}
	else
	{
		ft_strdel(&shell->hrdc_tmp);
		ft_strdel(&(*cmd)->process.stdin_send);
	}
}

void	hrdc_fill_stdin(t_prompt *prompt, t_cmd **cmd, t_shell *shell)
{
	char	*hrdc;

	if ((int)((*cmd)->process).stdin_send == -1)
		((*cmd)->process).stdin_send = ft_strdup("");
	hrdc = get_next_hrdc((*cmd)->hrdc);
	if (hrdc && shell->str && ft_strcmp(hrdc, shell->str) == 0)
		hrdc_match(prompt, cmd, shell);
	else if ((int)((*cmd)->process).stdin_send != -1)
	{
		ft_strjoin_free(&shell->hrdc_tmp, shell->str);
		ft_strjoin_free(&shell->hrdc_tmp, "\n");
		ft_strjoin_free(&((*cmd)->process).stdin_send, shell->str);
		ft_strjoin_free(&((*cmd)->process).stdin_send, "\n");
	}
	ft_strdel(&shell->str);
}

/*
** Le cas d'un CTRL-D, on save les HRDC enregistré dans stdin_send
** mais remet à NULL si rien
*/

int		hrdc_interrupt_ctrd(t_prompt *prompt, t_cmd **cmd, int nb_line)
{
	ft_dprintf(2, "42sh: warning: here-document at line %d delimited by "
		"end-of-file (wanted `%s')\n", nb_line, get_next_hrdc((*cmd)->hrdc));
	clean_cmd(&(*cmd)->start);
	*cmd = NULL;
	*prompt = PROMPT;
	return (1);
}

/*
** La première conditon correspond au Ctrl-C dans un heredoc
** La deuxième à un Ctrl-D (si cmd existe alors il attend des heredoc)
*/

int		hrdc_fill(t_prompt *prompt, t_cmd **cmd, t_shell *shell, t_shortcut ret)
{
	if (*prompt == HRDC && ret == CTRLD && !shell->str)
		return (hrdc_interrupt_ctrd(prompt, cmd, shell->count));
	else if (*prompt == HRDC && ret == CTRLC)
	{
		*prompt = PROMPT;
		shell->hist->cmd = ft_strdup(shell->hrdc_tmp);
		return (shell_clean_data(cmd, shell, 0));
	}
	if (*prompt == HRDC && *cmd)
	{
		hrdc_fill_stdin(prompt, cmd, shell);
		return (1);
	}
	return (0);
}
