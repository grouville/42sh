/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   backspace.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:10:17 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/02 00:35:39 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		last_char_pos(t_editor *ed)
{
	int i;
	int pos;

	i = 0;
	pos = ed->first_char;
	while (ed->hist->cmd && ed->hist->cmd[i])
	{
		if (ed->hist->cmd[i] == '\n' || pos == ed->ws_col)
			pos = 0;
		pos++;
		i++;
	}
	return (pos);
}

int		backspace(t_editor *ed)
{
	char *tmp;

	move_cursor_left(ed);
	if (ed->hist->cmd[ed->cursor_str_pos] == '\n')
		ed->last_row--;
	tmp = ft_strsub(ed->hist->cmd, 0, ed->cursor_str_pos);
	ft_strjoin_free(&tmp, ed->hist->cmd + ed->cursor_str_pos + 1);
	ft_strdel(&(ed->hist->cmd));
	if (ft_strlen(tmp))
	{
		ed->hist->cmd = tmp;
		ed->last_char = last_char_pos(ed);
	}
	else
		ft_strdel(&tmp);
	ft_putstr("\E[0J");
	ed->last_row = ed->first_row +
	nb_line(ed->hist->cmd, ed->first_char, ed->ws_col);
	print_line(ed->hist->cmd + ed->cursor_str_pos, 0, ed->cur_col, ed->ws_col);
	tputs(tgoto(tgetstr("cm", NULL), ed->cur_col - 1,
	ed->cur_row - 1), 1, ft_putchar);
	return (0);
}
