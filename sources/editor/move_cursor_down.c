/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_down.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 17:40:34 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/17 17:41:18 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		check_next_pos(t_editor *ed)
{
	int row_nb;
	int cur_col;
	int pos;

	row_nb = 0;
	cur_col = ed->cur_col;
	pos = ed->cursor_str_pos;
	while (ed->hist->cmd[pos])
	{
		if (ed->hist->cmd[pos] == '\n' || cur_col == ed->ws_col)
		{
			if (row_nb && ed->hist->cmd[pos] == '\n')
				break ;
			row_nb++;
			cur_col = 0;
		}
		cur_col++;
		pos++;
		if (cur_col == ed->cur_col)
			break ;
	}
	return (pos);
}

void	move_cursor_down(t_editor *ed)
{
	int pos;

	if (ed->cur_row < ed->last_row)
	{
		pos = check_next_pos(ed);
		while (pos > ed->cursor_str_pos)
			move_cursor_right(ed);
	}
}
