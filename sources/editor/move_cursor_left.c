/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_left.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 17:43:05 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/12 03:54:08 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	move_cursor_left(t_editor *ed)
{
	int tmp_pos;

	if (ed->cursor_str_pos > 0 && (tmp_pos = ed->cursor_str_pos - 1) >= 0)
	{
		ed->cursor_str_pos--;
		ed->cur_col--;
		if (ed->cur_col == 0)
		{
			if (!ed->rev_hist && ed->hist->cmd[ed->cursor_str_pos] == '\n')
			{
				go_to_begin_of_line(ed);
				while (ed->cursor_str_pos < tmp_pos)
					move_cursor_right(ed);
			}
			else
			{
				ed->cur_col = ed->ws_col;
				ed->cur_row--;
				tputs(tgoto(tgetstr("cm", NULL), ed->ws_col - 1,
				ed->cur_row - 1), 1, ft_putchar);
			}
		}
		else
			tputs(tgetstr("le", NULL), 1, ft_putchar);
	}
}
