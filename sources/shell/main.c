/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/16 11:01:40 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 16:35:55 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

BOOL	check_syntax_err(t_cmd *cmd)
{
	t_cmd	*next;

	next = cmd;
	while (next && (next = next->next_cmd))
	{
		if (!ft_strlen(next->args[0]) && next->sep)
		{
			write(2, "42sh: syntax error near unexpected token `", 42);
			if (next->sep == 1)
				write(2, "|'\n", 3);
			else if (next->sep == 2)
				write(2, ";'\n", 3);
			else if (next->sep == 3)
				write(2, "||'\n", 4);
			else if (next->sep == 4)
				write(2, "&&'\n", 4);
			else if (next->sep == 5)
				write(2, "&'\n", 3);
			return (1);
		}
		if (!stdout_to(next->output))
		{
			write(2, "42sh: syntax error near unexpected token `>'\n", 45);
			return (1);
		}
	}
	return (0);
}

BOOL	check_shrt(t_prompt *prompt, t_shortcut shortcut, t_shell *shl)
{
	char quote;

	if (shortcut == CTRLC && prompt != PROMPT)
		*prompt = PROMPT;
	if (shortcut == CTRLD || shortcut == CTRLC)
		ft_strdel(&shl->str);
	if (shortcut == CTRLD && *prompt == PROMPT)
		return (0);
	else if (shortcut == CTRLD && *prompt != PROMPT)
	{
		quote = (*prompt == S_QUOTE) ? (char)'\'' : (char)'"';
		ft_dprintf(2, "42sh: unexpected EOF while looking for matching `%c'\n"
				"42sh: syntax error: unexpected end of file\n", quote);
		*prompt = PROMPT;
	}
	return (1);
}

void	shell_save_histo(t_shell *shl)
{
	if (shl->hrdc_tmp)
		ft_strdel(&shl->str);
	shl->str = shl->hrdc_tmp ? ft_strdup(shl->hrdc_tmp) : shl->str;
	if (shl->str && ((!shl->hist->cmd && !shl->hist->prev) ||
					(shl->hist->prev && shl->hist->prev->cmd &&
					ft_strcmp(shl->hist->prev->cmd, shl->str))))
		shl->hist->cmd = ft_strdup(shl->str);
}

/*
** shl->str peut être mangé par hrdc_fill (pas besoin de split)
*/

int		shell(t_shell *shl, t_cmd **cmd, t_shortcut ret, t_prompt *prmt)
{
	if (ret != CTRLC && ret != CTRLD && shl->str && check_expansions(shl))
	{
		ft_strdel(&shl->str);
		return (1);
	}
	if (!hrdc_fill(prmt, cmd, shl, ret) && !check_shrt(prmt, ret, shl))
		return (-1);
	if ((shl->str && (*cmd = shell_split(shl->str, shl->envp, prmt))) ||
			(*prmt == PROMPT && *cmd && ((*cmd)->process).stdin_send))
	{
		if (cmd_check(cmd, shl, prmt))
			return (1);
		shell_save_histo(shl);
		if (check_syntax_err(*cmd))
			shell_clean_data(cmd, shl, 0);
		else if (shell_process(cmd, shl) == -1)
			return (-1);
	}
	return (0);
}

int		main(void)
{
	extern char **environ;
	t_shell		*shl;
	t_prompt	prmt;
	t_cmd		*cmd;
	t_shortcut	ret;

	shell_init(&shl, &prmt, &cmd, environ);
	while ((ret = get_stdin(shl, &prmt)) != -1)
	{
		if ((ret = shell(shl, &cmd, ret, &prmt)) == 1)
			continue ;
		else if (ret == -1)
			break ;/*
		if (ret != CTRLC && ret != CTRLD && shl->str && check_expansions(shl))
		{
			ft_strdel(&shl->str);
			continue ;
		}
		if (!hrdc_fill(&prmt, &cmd, shl, ret) && !check_shrt(&prmt, ret, shl))
			break ;
		printf("-<shellstr |%s|>\n", shl->str);
		if ((shl->str && (cmd = shell_split(shl->str, shl->envp, &prmt))) ||
			(prmt == PROMPT && cmd && (cmd->process).stdin_send))
		{
			if (cmd_check(&cmd, shl, &prmt))
				continue;
			shell_save_histo(shl);
			if (check_syntax_err(cmd))
				shell_clean_data(&cmd, shl, 0);
			else if (shell_process(&cmd, shl) == -1)
				break ;
		}*/
	}
	return (shell_exit(&cmd, &shl));
}
