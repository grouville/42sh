/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_history_incremental_search.c                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/02 16:23:00 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 13:38:19 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int				term_history_i_search_ndl(t_editor *ed, int *cur_tmp, int r)
{
	t_data	*tmp;
	char	*ndl;
	char	*hk_rev;

	hk_rev = NULL;
	tmp = ed->hist;
	ft_strrev(ed->ndl);
	while (tmp)
	{
		if (tmp->cmd && ft_strlen((ndl = ft_strstr(ft_strrev(
		hk_rev = ((unsigned long)tmp == (unsigned long)ed->hist ?
		ft_strsub(tmp->cmd, 0, *cur_tmp + ft_strlen(ed->ndl) - r) :
		ft_strdup(tmp->cmd))), ed->ndl))))
		{
			ed->hist = tmp;
			*cur_tmp = ft_strlen(ndl) - ft_strlen(ed->ndl);
			ft_strdel(&hk_rev);
			ft_strrev(ed->ndl);
			return (1);
		}
		ft_strdel(&hk_rev);
		tmp = tmp->prev;
	}
	ft_strrev(ed->ndl);
	return (0);
}

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
				,int mode, int *cursor_tmp)
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

int				term_history_i_search_exit(t_editor *ed,
				t_prompt prompt, int *cursor_tmp)
{
	char *tmp;

	tmp = ft_strdup(ed->key);
	ft_strdel(&ed->ndl);
	term_history_i_search_print_prompt(ed, prompt, 1, cursor_tmp);
	ed->key = tmp;
	ed->rev_hist = 0;
	return (ENTER_KEY ? 0 : 1);
}

void			term_history_i_search_backspace(t_editor *ed,
				int *cursor_tmp, t_prompt prompt)
{
	char *new;

	new = ft_strsub(ed->ndl, 0, ft_strlen(ed->ndl) - 1);
	ft_strdel(&ed->ndl);
	ed->ndl = new;
	term_history_i_search_print_prompt(ed, prompt, 0, cursor_tmp);
}

int				term_history_incremental_search(t_editor *ed, t_prompt prompt)
{
	int		cursor_tmp;

	cursor_tmp = ed->cursor_str_pos;
	ed->cursor_str_pos = ed->prompt_size;
	ft_strdel(&ed->key);
	while ((ed->ret = get_read_key(STDIN_FILENO, &ed->key)) != -1)
	{
		ed->rev_hist = 1;
		if (term_size(ed) == EXIT_SUCCESS)
			window_resize(ed, prompt, ed->hris);
		else if (LEFT_KEY || RIGHT_KEY || UP_KEY || DOWN_KEY || TAB_KEY ||
		ENTER_KEY || HOME_KEY || END_KEY || SHIFT_UP || SHIFT_DOWN ||
		SHIFT_RIGHT || SHIFT_LEFT || CTRL_A || CTRL_E || CTRL_C || CTRL_D)
			break ;
		else if (BACKSPACE && ft_strlen(ed->ndl))
			term_history_i_search_backspace(ed, &cursor_tmp, prompt);
		else if (!ed->ndl || (ed->key && (ft_isprint(ed->key[0]) || CTRL_R)))
			term_history_i_search_print_prompt(ed, prompt, 0, &cursor_tmp);
		ft_strdel(&ed->key);
	}
	return (term_history_i_search_exit(ed, prompt, &cursor_tmp));
}
