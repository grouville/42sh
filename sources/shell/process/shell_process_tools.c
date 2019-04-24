/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_tools.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/11 01:01:54 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/11 01:01:54 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	shell_prcs_sigint(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	shell_ret(t_cmd *elem, t_shell *shell)
{
	char *tmp;

	tmp = ft_itoa(elem->ret);
	if (!(check_replace_env_variable(&shell->envl, "?", tmp)))
		shell->envl = append_key_env(shell->envl, "?", tmp);
	ft_strdel(&tmp);
}

/*
** recherche le prochaine commande qui ne dépend pas du separateur {sep}
*/

t_cmd	*shell_process_skip_cmd(t_cmd *elem, t_sep sep)
{
	while (elem->sep == sep)
	{
		elem = elem->next_cmd;
		elem->completed = 1;
	}
	return (elem);
}
