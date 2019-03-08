/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_history_incremental_search.c                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/02 16:23:00 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/08 11:14:55 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int				term_history_search_needle(t_editor *ed, int *cursor_tmp)
{
	t_data *tmp;
	char *needle;
	char *cmd_rev;
	char *needle_rev;

	cmd_rev = NULL;
	tmp = ed->hist;
	ft_strrev(needle_rev = ft_strdup(ed->h_needle));
	while (tmp)
	{
		if (tmp->cmd && (needle = ft_strstr(ft_strrev(
		cmd_rev = ft_strdup(tmp->cmd)), needle_rev)) && ft_strlen(needle))
		{
			ed->hist = tmp;
			*cursor_tmp = ft_strlen(needle) - ft_strlen(ed->h_needle);
			ft_strdel(&cmd_rev);
			ft_strdel(&needle_rev);
			return (1);
		}
		ft_strdel(&cmd_rev);
		tmp = tmp->prev;
	}
	ft_strdel(&needle_rev);
	return (0);
}

void			term_history_print_prompt(t_editor *ed, t_prompt prompt, int mode, int *cursor_tmp)
{
	int		occurence;

	occurence = 1;
	while (ed->cursor_str_pos)
		move_cursor_left(ed);
	if ((!mode && !ed->h_needle) || mode)
		ft_putstr("\E[0J");
	if (!mode && !ed->h_needle)
		ed->h_needle = ft_strdup("");
	ft_putstr("\033[s");
	if (!mode)
	{
		ft_strjoin_free(&ed->h_needle, ed->key);
		if (ft_strlen(ed->h_needle))
		occurence = term_history_search_needle(ed, cursor_tmp);
		ed->hris = ft_strnew((occurence ? 22 : 29) + ft_strlen(ed->h_needle));
		ft_strcpy(ed->hris, occurence ? "(reverse-i-search)`" : "(failed reverse-i-search)`");
		ft_strcat(ed->hris, ed->h_needle);
		ft_strcat(ed->hris, "': ");
		ft_putstr(ed->hris);
	}
	else
		display_prompt(prompt);
	ft_putstr("\033[u");
	ed->cursor_str_pos = ed->cursor_str_pos - (mode ? ed->prompt_size : ft_strlen(ed->hris));
	while (ed->cursor_str_pos < 0)
		move_cursor_right(ed);
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
	ed->cursor_str_pos = ed->cursor_str_pos - *cursor_tmp;
	dprintf(2, "ed->cursor_str_pos: %d\ncursor_tmp: %d\n", ed->cursor_str_pos, *cursor_tmp);
	while (ed->cursor_str_pos)
		move_cursor_left(ed);
	ed->cursor_str_pos = *cursor_tmp + ft_strlen(ed->hris);
	ft_strdel(&ed->hris);
}

int				term_history_incremental_search(t_editor *ed, t_prompt prompt)
{
	int i;
	int cursor_tmp;
	i = 0;

	ed->rev_hist = 1;
	cursor_tmp = ed->cursor_str_pos;
	go_to_begin_of_line(ed);
	ed->cursor_str_pos = ed->prompt_size + ed->cursor_str_pos;
	ft_strdel(&ed->key);
	while ((ed->ret = get_read_key(STDIN_FILENO, &ed->key)) != -1)
	{
	//	if (term_size(ed) == EXIT_SUCCESS)
	//		window_resize(ed, )
		if (ed->ret && (LEFT_KEY || RIGHT_KEY || UP_KEY || DOWN_KEY ||
		TAB_KEY || ENTER_KEY || HOME_KEY || END_KEY || SHIFT_UP || SHIFT_DOWN
		|| SHIFT_RIGHT || SHIFT_LEFT || CTRL_C || CTRL_D))
				break ;
		else if (ed->ret && BACKSPACE)
			dprintf(2, "backspace\n");
		else if (!ed->h_needle || (ed->key && ft_isprint(ed->key[0])))
		{
			tputs(tgetstr("vi", NULL), 1, ft_putchar);
			term_history_print_prompt(ed, prompt, 0, &cursor_tmp);
			tputs(tgetstr("ve", NULL), 1, ft_putchar);
		}
		ft_strdel(&ed->key);
	}
	char *tmp;

	tmp = ft_strdup(ed->key);
	ft_strdel(&ed->h_needle);
	while (ed->cursor_str_pos)
		move_cursor_left(ed);
	ft_putstr("\E[0J");
	ft_putstr("\033[s");
	display_prompt(prompt);
	ft_putstr("\033[u");
	ed->cursor_str_pos = ed->cursor_str_pos - ed->prompt_size;
	while (ed->cursor_str_pos < 0)
			move_cursor_right(ed);
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
	ed->key = tmp;
	ed->rev_hist = 0;
	return (ENTER_KEY ? 0 : 1);
}
