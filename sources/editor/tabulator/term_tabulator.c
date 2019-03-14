/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_tabulator.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/07 16:25:14 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 05:30:43 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

t_tab	*tabulator_init(int cursor_pos, char **envp, char **envl)
{
	t_tab *tabu;

	if (!(tabu = (t_tab*)malloc(sizeof(t_tab))))
		return (NULL);
	tabu->path = NULL;
	tabu->data = NULL;
	tabu->home = NULL;
	tabu->comp = NULL;
	tabu->dir = NULL;
	tabu->elem = NULL;
	tabu->last_elem = NULL;
	tabu->env = envp;
	tabu->envl = envl;
	tabu->nb_col = 0;
	tabu->nb_row = 0;
	tabu->max_len = 0;
	tabu->nb_node = 0;
	tabu->mode = 0;
	tabu->start = cursor_pos;
	tabu->end = cursor_pos;
	return (tabu);
}

int		tabulator_read(t_tab *tabu, t_editor *ed, int mode)
{
	int ret;

	ft_strdel(&ed->key);
	!mode ? ft_dprintf(1, "Display all %d possibilities? (y or n)",
			tabu->nb_node) : ft_putstr("--More--");
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	while ((ret = get_read_key(STDIN_FILENO, &ed->key)) > -1)
	{
		if (!mode && ret == 1 && ed->key[0] == 'y' && write(1, "\n", 1))
			return (1);
		else if ((!mode && ret == 1 && (ed->key[0] == 'n' || ed->key[0] == 127)
		&& write(1, "\n", 1)) || (mode && ret == 1 && ed->key[0] == 127))
			return (0);
		else if (mode && ret == 1 && ed->key[0] == '\n')
			break ;
		else if (term_size(ed) == EXIT_SUCCESS)
			continue ;
		else if (ret && ed->key && CTRL_C)
			return (-3);
		ft_strdel(&ed->key);
	}
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar);
	ft_putstr("\E[J");
	tabu->nb_node++;
	return (ret);
}

int		tabulator_put_row(t_editor *ed, t_tab *tabu, t_prompt *prompt)
{
	int		ret;

	ret = 0;
	go_to_end_of_line(ed);
	write(1, "\n", 1);
	if (!tabu->nb_row && tabu->nb_node > 1)
		tabulator_one_row(tabu->elem, tabu->max_len);
	else if (((ret = tabulator_multi_row(tabu, ed)) == -1 || ret == -3))
		return (ret);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar);
	ft_putstr("\E[J");
	ed->prompt_size = display_prompt(*prompt);
	ed->first_char = get_cursor_position(0);
	ed->first_row = get_cursor_position(1);
	print_line(ed->hist->cmd, 0, ed->first_char, ed->ws_col);
	calculate_first_and_last_row(ed);
	ed->last_char = last_char_pos(ed);
	ed->cur_row = ed->last_row;
	ed->cursor_str_pos = ft_strlen(ed->hist->cmd);
	ed->cur_col = ed->last_char;
	while (ed->cursor_str_pos > tabu->save_pos)
		move_cursor_left(ed);
	return (ret);
}

int		term_tabulator(t_editor *ed, t_prompt *prompt, char **envp, char **envl)
{
	t_tab	*tabu;
	int		ret;

	ret = 0;
	tabu = tabulator_init(ed->cursor_str_pos, envp, envl);
	tabulator_recup_data(ed, tabu);
	if (tabu->nb_node)
	{
		if (tabu->nb_node == 1 || tabu->comp)
		{
			if (term_tabulator_enough_space(ed, tabu))
				tabulator_put_new_cmd(tabu, ed);
		}
		else
			ret = tabulator_put_row(ed, tabu, prompt);
	}
	free_tab(tabu);
	if (!CTRL_C)
		ft_strdel(&ed->key);
	return (ret);
}
