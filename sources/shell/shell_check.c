/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_check.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 00:43:10 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/07 00:43:10 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	shell_prepare_alias(t_cmd *elem, char *alias_var)
{
	int			nb_arg;
	char		**args;
	int			i;
	int			n;
	char		*tmp;

	tmp = alias_var;
	if (ft_strchr("'\"", alias_var[0]))
	{
		alias_var++;
		alias_var[ft_strlen(alias_var) - 1] = '\0';
	}
	nb_arg = get_nbarg(alias_var, 0);
	args = (char **)malloc(sizeof(char *) * (nb_arg + ft_arrlen(elem->args)));
	args[nb_arg + ft_arrlen(elem->args) - 1] = NULL;
	i = 0;
	while (i < nb_arg)
		args[i++] = get_arg(&alias_var, elem);
	ft_strdel(&tmp);
	n = 1;
	while (elem->args[n])
		args[i++] = ft_strdup(elem->args[n++]);
	i = 0;
	ft_arrdel(&elem->args);
	elem->args = args;
}

BOOL	shell_hrdc_quotesub(t_cmd *cmd, t_shell *shell, t_prompt *prompt)
{
	int i;

	ft_strjoin_free(&shell->hrdc_tmp, shell->str);
	ft_strjoin_free(&shell->hrdc_tmp, "\n");
	ft_strdel(&shell->str);
	*prompt = HRDC;
	i = 0;
	while (cmd->hrdc[i] != NULL)
		shl_quotesub(cmd->hrdc[i++]);
	return (1);
}

/*
** -1 pour un hrdc malloc mais interrompu par Ctrl-C/D
** -2 pour une valeur attendu manquante (cat <)
** On del shell->str car déjà exploité dans cmd->split
*/

BOOL	cmd_check_error(t_cmd *next, t_shell *shell)
{
	if ((next->hrdc && (int)next->hrdc[0] == -1) ||
		(((next->input && (int)next->input[0] == -2) ||
		  (next->hrdc && (int)next->hrdc[0] == -2)) &&
		 next->next_cmd == NULL))
	{
		write(2, "42sh: syntax error near unexpected token `newline'\n",
			  51);
		ft_strdel(&shell->str);
		return (1);
	}
	return (0);
}

BOOL	cmd_check(t_cmd **cmd, t_shell *shell, t_prompt *prompt)
{
	t_cmd	*next;

	*cmd = (*cmd)->start;
	next = *cmd;
	while ((next = next->next_cmd))
	{
		if (get_envp(shell->alias, next->args[0]))
			shell_prepare_alias(next,
							ft_strdup(get_envp(shell->alias, next->args[0])));
		//if (!check_expansions(next, shell))
		//	return (1);
		if (next->hrdc && ((int)next->hrdc[0] < -3 || (int)next->hrdc[0] > -1))
			return (shell_hrdc_quotesub((*cmd = next), shell, prompt));
		if (cmd_check_error(next, shell))
		{
			clean_cmd(cmd);
			return (1);
		}
	}
	return (0);
}
