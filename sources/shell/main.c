/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/16 11:01:40 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 12:07:36 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

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
	if (shl->hist->cmd)
		shl->hist = hist_add(shl->hist);
}

void	shell_check_backslash_end(char **line)
{
	int		i;
	char	*del;

	i = 0;
	while (*line && (*line)[i])
	{
		if (i > 0 && (*line)[i] == 10 && (*line)[i - 1] == '\\')
		{
			del = ft_strcutword(line, i - 1, 2);
			ft_strdel(&del);
			return ;
		}
		i++;
	}
}

/*
** shl->str peut être mangé par hrdc_fill (pas besoin de split)
*/

int		shell_command_execution(t_shell *shl, t_cmd **cmd, t_shortcut ret,
									t_prompt *prmt)
{
	if (ret != CTRLC && ret != CTRLD && shl->str && check_expansions(shl))
	{
		ft_strdel(&shl->str);
		return (1);
	}
	if (!hrdc_fill(prmt, cmd, shl, ret) && !check_shrt(prmt, ret, shl))
		return (-1);
	if (*prmt == PROMPT)
		shell_check_backslash_end(&shl->str);
	shl->str = shell_alias(shl->str, shl->alias);
	if ((shl->str && ((*cmd) = shell_split(shl->str, shl->envp, prmt))) ||
			(*prmt == PROMPT && *cmd && ((*cmd)->process).stdin_send))
	{
		if (cmd_check(cmd, shl, prmt))
			return (1);
		shell_save_histo(shl);
		if (check_syntax_err(*cmd))
			return (shell_clean_data(cmd, shl, 0));
		else if (shell_process(getter_job()->first_job, cmd, shl) == -1)
			return (-1);
	}
	return (0);
}

int		main(void)
{
	t_norme			norme;

	ft_bzero(&norme, sizeof(t_norme));
	shell_init(&norme.shl, &norme.prmt, &norme.cmd, &norme.jobs);
	while ((norme.ret = get_stdin(norme.shl, &norme.prmt)) != -1)
	{
		norme.shl->count += 1;
		if (!norme.shl->str && norme.prmt == PROMPT)
			do_job_notification(&norme.cmd, norme.shl, NULL);
		norme.ret = shell_command_execution(norme.shl, &norme.cmd,
				norme.ret, &norme.prmt);
		if (norme.ret == -1 && !check_jobs_on_exit(norme.shl))
			break ;
		if (norme.shl->str && norme.prmt == PROMPT)
			ft_strdel(&norme.shl->str);
	}
	return (shell_exit(&norme.shl));
}
