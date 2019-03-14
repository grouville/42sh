/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   paste_line.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 20:34:38 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/12 05:37:46 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	add_paste_into_line(t_editor *ed)
{
	int		tmp_last_pos;
	char	*tmp;

	tmp_last_pos = ed->cursor_str_pos + ft_strlen(ed->key);
	if (ed->hist->cmd)
	{
		tmp = ft_strsub(ed->hist->cmd, 0, ed->cursor_str_pos);
		ft_strjoin_free(&tmp, ed->key);
		ft_strjoin_free(&tmp, ed->hist->cmd + ed->cursor_str_pos);
		ft_strdel(&ed->hist->cmd);
		ed->hist->cmd = tmp;
	}
	else
		ed->hist->cmd = ft_strdup(ed->key);
	print_line(ed->hist->cmd, ed->cursor_str_pos, ed->cur_col, ed->ws_col);
	ed->last_char = last_char_pos(ed);
	ed->cur_col = ed->last_char;
	calculate_first_and_last_row(ed);
	ed->cur_row = ed->last_row;
	ed->cursor_str_pos = ft_strlen(ed->hist->cmd);
	while (ed->cursor_str_pos > tmp_last_pos)
		move_cursor_left(ed);
}
