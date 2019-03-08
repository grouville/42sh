/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_up.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 17:42:14 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/17 17:42:31 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		check_prev_pos(t_editor *ed)
{
	int pos;
	int cur_row;
	int cur_col;

	pos = 0;
	cur_row = ed->first_row;
	cur_col = ed->first_char;
	while (ed->hist->cmd[pos])
	{
		if (cur_col == ed->ws_col || ed->hist->cmd[pos] == '\n')
		{
			cur_col = 0;
			cur_row++;
		}
		cur_col++;
		pos++;
		if (cur_row == ed->cur_row - 1 && ((ed->hist->cmd[pos] == '\n' &&
		cur_col <= ed->cur_col) || cur_col == ed->cur_col))
			break ;
	}
	return (pos);
}

void	move_cursor_up(t_editor *ed)
{
	int pos;

	if (ed->cur_row > ed->first_row)
	{
		if (ed->cur_row - 1 == ed->first_row && ed->first_char >= ed->cur_col)
			pos = 0;
		else
			pos = check_prev_pos(ed);
		while (pos < ed->cursor_str_pos)
			move_cursor_left(ed);
	}
}
