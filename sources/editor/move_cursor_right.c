/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_cursor_right.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 17:43:44 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 16:30:26 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	move_cursor_right(t_editor *ed)
{
	if ((int)ed->cursor_str_pos < ft_strlen(ed->hist->cmd))
	{
		if ((!ed->rev_hist && ed->hist->cmd[ed->cursor_str_pos] == '\n') ||
		ed->cur_col == ed->ws_col)
		{
			ed->cur_col = 0;
			ed->cur_row++;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		}
		else
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
		ed->cur_col++;
		ed->cursor_str_pos++;
	}
}
