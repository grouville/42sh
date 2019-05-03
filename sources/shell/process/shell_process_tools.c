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
	unsigned char ret;

	ret = 0;
	if (elem->ret == 256 || elem->bad_substitution || elem->ret == 1)
		ret = 1;
	else if (elem->ret == 4735)
		ret = 146;
	else if (elem->ret == 16384)
		ret = 64;
	else if (elem->ret == 32256)
		ret = 126;
	else if (elem->ret == 32512)
		ret = 127;
	else if (elem->ret == 3)
		ret = 131;
	if (ret >= 0)
		shell->ret = (int)ret;
	tmp = ft_itoa(shell->ret);
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
		elem->done = 1;
	}
	return (elem);
}
