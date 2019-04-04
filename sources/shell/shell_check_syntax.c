/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_check_syntax.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 15:36:08 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/02 15:36:08 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** -1 pour un hrdc malloc mais interrompu par Ctrl-C/D
*/

BOOL	cmd_syntax_shortcut(t_cmd *next)
{
	if (next->hrdc && (int)next->hrdc[0] == -1)
	{
		ft_dprintf(2, "42sh: syntax error near unexpected token `newline'\n");
			return (1);
	}
	return (0);
}

/*
** -2 pour un hrdc ou input indiqué mais non rempli (cat <) || (cat <<)
*/

BOOL	check_syntax_redi(t_cmd *next)
{
	//int last;

	if (!stdout_to(next->output))
	{
		write(2, "42sh: syntax error near unexpected token `>'\n", 45);
		return (1);
	}
	if ((int)next->process.stdin_send == -2)
	{
		ft_dprintf(2, "42sh: syntax error near unexpected token `<'\n");
		return (1);
	}
	//pourquoi voir que le [0] ? et hrdc plante always lors de son free
	if (((next->input && (int)next->input[0] == -2) ||
	  (next->hrdc && (int)next->hrdc[0] == -2)) && next->next_cmd == NULL)
	{
		ft_dprintf(2, "42sh: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

BOOL	check_syntax_sep(t_cmd *next)
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
	return (0);
}

BOOL	check_syntax_err(t_cmd *cmd)
{
	t_cmd	*next;

	next = cmd;
	while (next && (next = next->next_cmd))
	{
		if (check_syntax_sep(next) || check_syntax_redi(next) ||
			cmd_syntax_shortcut(next))
			return (1);
	}
	return (0);
}