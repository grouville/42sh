/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   paste_clipboard.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 15:40:27 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/20 08:10:10 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

static void		paste_clipboard_into_line(t_editor *ed)
{
	int		last_pos;
	char	*tmp;

	last_pos = ed->cursor_str_pos + ft_strlen(ed->clipboard);
	tmp = ft_strsub(ed->hist->cmd, 0, ed->cursor_str_pos);
	ft_strjoin_free(&tmp, ed->clipboard);
	ft_strjoin_free(&tmp, ed->hist->cmd + ed->cursor_str_pos);
	ft_strdel(&(ed->hist->cmd));
	if (ft_strlen(tmp))
		ed->hist->cmd = tmp;
	else
		ft_strdel(&tmp);
	ft_putstr("\E[J");
	print_line(ed->hist->cmd, ed->cursor_str_pos, ed->cur_col, ed->ws_col);
	ed->cursor_str_pos = ft_strlen(ed->hist->cmd);
	ed->last_char = last_char_pos(ed);
	ed->cur_col = ed->last_char;
	calculate_first_and_last_row(ed);
	ed->cur_row = ed->last_row;
	while (ed->cursor_str_pos > last_pos)
		move_cursor_left(ed);
}

void			paste_clipboard(t_editor *ed)
{
	if (ed->clipboard)
	{
		paste_clipboard_into_line(ed);
	}
}
