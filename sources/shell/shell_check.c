/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_check.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 00:43:10 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/16 11:03:37 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	shell_prepare_alias(t_cmd *elem, char *alias_var, int index)
{
	int			nb_arg;
	char		**args;
	int			i;
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
	i = -1;
	while (++i < index)
		args[i] = ft_strdup(elem->args[i]);
	while (nb_arg--)
		args[i++] = get_arg(&alias_var, elem);
	ft_strdel(&tmp);
	while (elem->args[++index])
		args[i++] = ft_strdup(elem->args[index]);
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

void	shell_check_alias_chained(t_shell *shell, t_cmd *next, char **last_alias
		, int index)
{
	int i;

	if (*last_alias)
	{
		shl_quotesub(*last_alias);
		if (next->args[index + get_nbarg(*last_alias, 0)])
		{
			if ((*last_alias)[ft_strlen(*last_alias) - 1] == ' ')
			{
				i = get_nbarg(*last_alias, 0);
				ft_strdel(last_alias);
				shell_check_alias(shell, next, index + i);
			}
		}
		ft_strdel(last_alias);
	}
}

void	shell_check_alias(t_shell *shell, t_cmd *next, int index)
{
	int i;
	char **alias_check;
	char *last_alias;
	char *tmp;

	i = -1;
	last_alias = NULL;
	alias_check = ft_arrdup(shell->alias);
	while (alias_check && alias_check[++i])
	{
		if (ft_strcmp((tmp = get_var(alias_check[i])), next->args[index]) == 0)
		{
			ft_strdel(&last_alias);
			last_alias = get_value(alias_check[i]);
			shell_prepare_alias(next,
			ft_strdup(get_envp(alias_check, next->args[index])), index);
			alias_check = rmv_key_env(alias_check, tmp);
			i = -1;
		}
		ft_strdel(&tmp);
	}
	ft_arrdel(&alias_check);
	shell_check_alias_chained(shell, next, &last_alias, index);
}

BOOL	cmd_check(t_cmd **cmd, t_shell *shell, t_prompt *prompt)
{
	t_cmd	*next;

	*cmd = (*cmd)->start;
	next = *cmd;
	while ((next = next->next_cmd))
	{
		if (shell->alias && ft_arrlen(shell->alias))
			shell_check_alias(shell, next, 0);
		if (next->hrdc && ((int)next->hrdc[0] < -3 || (int)next->hrdc[0] > -1))
			return (shell_hrdc_quotesub((*cmd = next), shell, prompt));
	}
	return (0);
}
