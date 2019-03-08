/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_stdin.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/12 00:01:33 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/07 18:08:10 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

static void		get_stdin_next(char **line, t_editor *ed, t_prompt *prompt,
				t_data **hist)
{
	go_to_end_of_line(ed);
	ft_putchar('\n');
	if (*prompt != PROMPT)
	{
		if (ed->hist->cmd)
			ft_strjoin_free(line, ed->hist->cmd);
	}
	else
		*line = ft_strdup(ed->hist->cmd);
	while ((*hist)->next)
		*hist = (*hist)->next;
}

static void		get_keyboard_key_ctrl(t_editor *ed, t_prompt *p)
{
	if (CTRL_D && !ed->hist->cmd)
		ed->ret = -2;
	else if (CTRL_C)
	{
		go_to_end_of_line(ed);
		ed->ret = -3;
	}
	else if (ed->first_row < 1)
		return ;
	else if (CTRL_L)
		clear_window(ed, *p);
	else if (CTRL_K && (ft_strlen(ed->hist->cmd) + ed->cursor_str_pos))
		delete_from_cursor_to_end(ed);
	else if (CTRL_P && enough_space_on_screen(ed))
		paste_clipboard(ed);
}

static int		get_keyboard_key(t_editor *ed, t_prompt *prompt,
				char **envp, char **envl)
{
	if (CTRL_D || CTRL_C || CTRL_L || CTRL_K || CTRL_P)
		get_keyboard_key_ctrl(ed, prompt);
	else if (ed->first_row < 1)
		return (0);
	else if (LEFT_KEY || RIGHT_KEY)
		LEFT_KEY ? move_cursor_left(ed) : move_cursor_right(ed);
	else if ((SHIFT_LEFT || SHIFT_RIGHT) && ed->hist->cmd)
		SHIFT_LEFT ? move_word_left(ed) : move_word_right(ed);
	else if (SHIFT_UP || SHIFT_DOWN)
		SHIFT_UP ? move_cursor_up(ed) : move_cursor_down(ed);
	else if (HOME_KEY || CTRL_A || END_KEY || CTRL_E)
		HOME_KEY || CTRL_A ? go_to_begin_of_line(ed) : go_to_end_of_line(ed);
	else if (ft_isprint(ed->key[0]) && enough_space_on_screen(ed))
		return (print_key(ed));
	else if (BACKSPACE && ed->hist->cmd && ed->cursor_str_pos)
		backspace(ed);
	else if (TAB_KEY)
		ed->ret = term_tabulator(ed, prompt, envp, envl);
	else if ((UP_KEY || DOWN_KEY))
		term_history(ed);
	else if (CTRL_R)
		if ((ed->ret = term_history_incremental_search(ed, *prompt)))
			get_keyboard_key(ed, prompt, envp, envl);
	return (EXIT_SUCCESS);
}

int				get_stdin(t_shell *shell, t_prompt *prompt)
{
	t_editor	*ed;

	get_term_raw_mode(1);
	if (!(ed = line_editor_init(&shell->str, *prompt,
			display_prompt(*prompt), &shell->hist)))
		return (-2);
	while (isatty(STDIN_FILENO) &&
	(ed->ret = get_read_key(STDIN_FILENO, &ed->key)) != - 1)
	{
		tputs(tgetstr("vi", NULL), 1, ft_putchar);
		if (term_size(ed) == EXIT_SUCCESS)
			window_resize(ed, prompt);
		if (ed->ret && ed->key)
			get_keyboard_key(ed, prompt, shell->envp, shell->envl);
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
		if (ed->key && (ENTER_KEY ||
		(CTRL_D && !ed->hist->cmd) || CTRL_C))
			break ;
		ft_strdel(&ed->key);
	}
	get_stdin_next(&shell->str, ed, prompt, &shell->hist);
	get_term_raw_mode(0);
	return (line_editor_delete(ed, &shell->hist));
}
