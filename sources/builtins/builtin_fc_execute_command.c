/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc_execute_command.c                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 13:00:45 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 22:11:26 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

static void		builtin_fc_remove_hist_node(t_shell *shell, int mode)
{
	t_data *tmp;
	t_data *tmp1;

	if (mode)
	{
		tmp = shell->hist->prev;
		shell->hist = shell->hist->prev->prev;
		while (tmp)
		{
			if (tmp->cmd)
				ft_strdel(&tmp->cmd);
			tmp1 = tmp->next;
			free(tmp);
			tmp = tmp1;
		}
	}
	else
	{
		tmp = shell->hist;
		shell->hist = shell->hist->prev;
		free(tmp);
	}
	ft_strdel(&shell->hist->cmd);
	shell->hist->next = NULL;
}

static void		builtin_fc_error(t_fc *fc, t_prompt prompt,
					t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = *cmd;
	if (prompt == HRDC)
		while (tmp)
		{
			i = -1;
			while (tmp->hrdc[++i])
				ft_dprintf(2, "42sh: warning: here-document at line %d "
				"delimited "
				"by end-of-file (wanted `%s')\n", (unsigned long)tmp ==
				(unsigned long)*cmd && tmp->next_cmd ? fc->heredoc[0] :
				fc->heredoc[1], tmp->hrdc[i]);
			tmp = tmp->next_cmd;
		}
	clean_cmd(cmd);
}

static void		builtin_fc_execute_commands_list(t_fc *fc, t_prompt *p,
				t_cmd **cmd, t_shell *shell)
{
	t_data			*tmp;
	unsigned long	cmd_addr;

	cmd_addr = 0;
	fc->cmd_list = init_hist("/tmp/.42sh-fc_cmd_list");
	while (fc->cmd_list && fc->cmd_list->prev)
		fc->cmd_list = fc->cmd_list->prev;
	while (fc->cmd_list && ((tmp = fc->cmd_list->next) || !tmp))
	{
		fc->heredoc[1] = fc->cmd_list->cmd ? fc->heredoc[1] + 1 :
		fc->heredoc[1] + 0;
		if ((shell->str = fc->cmd_list->cmd) && write(1, fc->cmd_list->cmd,
		ft_strlen(fc->cmd_list->cmd)) && write(1, "\n", 1) &&
		(fc->ret = shell_command_execution(shell, cmd, 0, p) == -1))
		{
			fc->cmd_list->cmd = NULL;
			return ;
		}
		if (*p != PROMPT && (!fc->heredoc[0] || ((*cmd && cmd_addr !=
		(unsigned long)*cmd) && (cmd_addr = (unsigned long)*cmd))))
			fc->heredoc[0] = fc->heredoc[1];
		free(fc->cmd_list);
		fc->cmd_list = tmp;
	}
}

void			builtin_fc_execute_commands(t_fc *fc, t_shell *shell)
{
	t_prompt	p;
	t_cmd		*cmd;

	p = PROMPT;
	cmd = NULL;
	if (!fc->op || (!ft_strchr(fc->op, 's') && ft_strchr(fc->op, 'e')))
		fc->ret = shell_command_execution(shell, &cmd, 0, &p);
	builtin_fc_remove_hist_node(shell, fc->editor ? 1 : 0);
	ft_strdel(&shell->str);
	if (fc->ret != 0 || ((ft_atoi(get_envp(shell->envl, "?"))) >= 1))
	{
		fc->ret = fc->ret != -1 ? ft_atoi(get_envp(shell->envl, "?")) : fc->ret;
		return ;
	}
	builtin_fc_execute_commands_list(fc, &p, &cmd, shell);
	fc->ret = fc->ret != -1 ? ft_atoi(get_envp(shell->envl, "?")) : fc->ret;
	if (p != PROMPT)
		builtin_fc_error(fc, p, &cmd);
}
