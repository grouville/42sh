/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_history.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/06 17:20:14 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/20 03:20:05 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	term_history_up(t_editor *ed, char *line)
{
	t_data *tmp;

	tmp = NULL;
	if (!ed->hist->next)
	{
		if (ft_strlen(line) && !ft_strcmp(ed->hist->cmd, line))
			ed->hist = ed->hist->prev;
	}
	else
	{
		if (!ed->hist->prev)
			tmp = ed->hist;
		ed->hist = tmp ? tmp : ed->hist->prev;
	}
}

void	term_history_down(t_editor *ed)
{
	t_data *tmp;

	tmp = NULL;
	if (!ed->hist->next)
		tmp = ed->hist;
	ed->hist = tmp ? tmp : ed->hist->next;
}

void	term_history_put_cmd(t_editor *ed)
{
	go_to_begin_of_line(ed);
	ft_putstr("\E[J");
	if (ed->hist->cmd)
		print_line(ed->hist->cmd, 0, ed->first_char, ed->ws_col);
	ed->cursor_str_pos = ft_strlen(ed->hist->cmd);
	ed->last_char = last_char_pos(ed);
	if (ed->last_char - 1 == ed->ws_col)
	{
		tputs(tgetstr("do", NULL), 1, ft_putchar);
		ed->last_char = 1;
	}
	calculate_first_and_last_row(ed);
	ed->cur_row = ed->last_row;
	ed->cur_col = ed->last_char;
}

void	term_history(t_editor *ed)
{
	if (UP_KEY)
	{
		if (ed->hist->prev)
		{
			ed->hist = ed->hist->prev;
			term_history_put_cmd(ed);
		}
	}
	else
	{
		if (ed->hist->next)
		{
			ed->hist = ed->hist->next;
			term_history_put_cmd(ed);
		}
	}
}
