/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_char.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 10:42:22 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 17:13:29 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int				check_if_new_line_in_line(t_editor *ed)
{
	int i;
	int pos;

	i = ed->cursor_str_pos;
	pos = ed->cur_col;
	while (ed->hist->cmd && ed->hist->cmd[i])
	{
		if (ed->hist->cmd[i] == '\n')
			return (pos);
		if (pos == ed->ws_col)
			pos = 0;
		i++;
		pos++;
	}
	return (-1);
}

static void		add_char_into_line_2(t_editor *ed)
{
	char	*tmp;

	tmp = ft_strsub(ed->hist->cmd, 0, ed->cursor_str_pos);
	ft_strjoin_free(&tmp, ed->key);
	ft_strjoin_free(&tmp, ed->hist->cmd + ed->cursor_str_pos);
	ft_strdel(&(ed->hist->cmd));
	ed->hist->cmd = tmp;
	print_line(ed->hist->cmd, ed->cursor_str_pos, ed->cur_col, ed->ws_col);
	ed->last_char = last_char_pos(ed);
	if (ed->cur_col == ed->ws_col)
	{
		ed->cur_col = 0;
		ed->cur_row++;
	}
	calculate_first_and_last_row(ed);
	ed->cursor_str_pos++;
	ed->cur_col++;
}

void			add_char_into_line(t_editor *ed, int pos)
{
	if (pos == ed->ws_col ||
	(pos == -1 && ed->last_row == ed->ws_row && ed->last_char == ed->ws_col))
	{
		ft_putstr("\E[J");
		if (ed->last_row == ed->ws_row)
		{
			ed->first_row--;
			ed->cur_row--;
		}
		else
			ed->last_row++;
	}
	add_char_into_line_2(ed);
	tputs(tgoto(tgetstr("cm", NULL),
	ed->cur_col - 1, ed->cur_row - 1), 1, ft_putchar);
}

int				print_key(t_editor *ed)
{
	if (ft_strlen(ed->key) == 1)
		add_char_into_line(ed, check_if_new_line_in_line(ed));
	else
		add_paste_into_line(ed);
	return (EXIT_SUCCESS);
}
