/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_history_incremental_search_print.c          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 15:37:56 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 15:44:06 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void			term_history_i_search_print_line(t_editor *ed, int cursor_tmp,
				int mode)
{
	ft_putstr("\033[u");
	ed->cursor_str_pos = ed->cursor_str_pos -
	(mode ? ed->prompt_size : ft_strlen(ed->hris));
	while (ed->cursor_str_pos < 0)
		move_cursor_right(ed);
	ft_putstr("\E[0J");
	ed->first_char = ed->cur_col;
	ed->last_char = ed->cur_col;
	ed->first_row = ed->cur_row;
	ed->last_row = ed->cur_row;
	ed->cursor_str_pos = 0;
	ft_strdel(&ed->key);
	ed->key = ft_strdup(ed->hist->cmd);
	ft_strdel(&ed->hist->cmd);
	print_key(ed);
	ft_strdel(&ed->key);
	ed->cursor_str_pos = ed->cursor_str_pos - cursor_tmp;
	ed->rev_hist = 0;
	go_to_begin_of_line(ed);
	while (ed->cursor_str_pos < cursor_tmp)
		move_cursor_right(ed);
	ed->cursor_str_pos = !mode ? ft_strlen(ed->hris) : cursor_tmp;
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
}

void			term_history_i_search_print_prompt(t_editor *ed, t_prompt prompt
				, int mode, int *cursor_tmp)
{
	int		occur;

	ft_strdel(&ed->hris);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	go_to_begin_of_line(ed);
	ed->ndl = !mode && !ed->ndl ? ft_strdup("") : ed->ndl;
	while (ed->cursor_str_pos)
		move_cursor_left(ed);
	ft_putstr("\033[s");
	if (!mode)
	{
		if (!BACKSPACE && !CTRL_R)
			ft_strjoin_free(&ed->ndl, ed->key);
		if ((occur = 1) && ft_strlen(ed->ndl))
			occur = term_history_i_search_ndl(ed, cursor_tmp, CTRL_R ? 1 : 0);
		ed->hris = ft_strnew((occur ? 22 : 29) + ft_strlen(ed->ndl));
		ft_strcpy(ed->hris, occur ? "(reverse-i-search)`"
		: "(failed reverse-i-search)`");
		ft_strcat(ed->hris, ed->ndl);
		ft_strcat(ed->hris, "': ");
		ft_putstr(ed->hris);
	}
	else
		display_prompt(prompt);
	term_history_i_search_print_line(ed, *cursor_tmp, mode);
}
