/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator_check_mode.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/28 12:06:32 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/09 14:23:01 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		check_separator(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '(')
		return (1);
	return (0);
}

int		check_if_cmd(t_editor *ed)
{
	int start;

	start = ed->cursor_str_pos ? ed->cursor_str_pos - 1 : 0;
	if (!start && ed->hist->cmd[start] == ' ')
		return (1);
	else if (!start)
		return (0);
	while (start >= 0)
	{
		if (check_separator(ed->hist->cmd[start]))
			break ;
		if (ed->hist->cmd[start] >= 33 && ed->hist->cmd[start] <= 126)
			return (0);
		start--;
	}
	start = ed->cursor_str_pos ? ed->cursor_str_pos - 1 : 0;
	while (ed->hist->cmd[start])
	{
		if (ed->hist->cmd[start] >= 33 && ed->hist->cmd[start] <= 126)
			return (1);
		start++;
	}
	return (1);
}

int		tabulator_check_cmd(t_editor *ed, t_tab *tabu)
{
	int check;

	tabu->start = ed->cursor_str_pos;
	while (--tabu->start >= -1)
		if ((tabu->start == -1 || (tabu->start >= 0 && check_separator(
		ed->hist->cmd[tabu->start])) || (tabu->start == 0 && ed->hist->cmd
		[tabu->start] == ' ')) || (tabu->start > 0 && ed->hist->cmd
		[tabu->start] == ' ' && ed->hist->cmd[tabu->start - 1] != '\\')
		|| (tabu->start >= 0 && (ed->hist->cmd[tabu->start] == '<' ||
		ed->hist->cmd[tabu->start] == '>')))
		{
			tabu->start++;
			break ;
		}
	check = tabu->start;
	while (--check >= 0 && !check_separator(ed->hist->cmd[check]))
		if (ed->hist->cmd[check] >= 33 && ed->hist->cmd[check] <= 126)
			return (0);
	tabu->path = ft_strsub(ed->hist->cmd, tabu->start,
	ed->cursor_str_pos - tabu->start);
	return (1);
}

void	tabulator_check_argument(t_editor *ed, t_tab *tabu)
{
	tabu->start = ed->cursor_str_pos;
	while (--tabu->start >= 0)
	{
		if ((ed->hist->cmd[tabu->start] == ' ' ||
		ed->hist->cmd[tabu->start] == '<' ||
		ed->hist->cmd[tabu->start] == '>') &&
		((tabu->start && ed->hist->cmd[tabu->start - 1] != '\\')
		|| !tabu->start))
		{
			tabu->start++;
			break ;
		}
	}
	if (tabu->start == -1)
		tabu->start++;
	tabu->path = ed->cursor_str_pos - tabu->start ? ft_strsub(ed->
	hist->cmd, tabu->start, ed->cursor_str_pos -
	tabu->start) : tabu->path;
}

int		tabulator_get_path(t_editor *ed, t_tab *tabu)
{
	if (!tabu->start || (tabu->start && check_if_cmd(ed)))
		return (0);
	else if (tabulator_check_cmd(ed, tabu))
		return (tabu->path && tabu->path[0] == '$' ? 3 : 1);
	else
		tabulator_check_argument(ed, tabu);
	return (tabu->path && tabu->path[0] == '$' ? 3 : 2);
}
