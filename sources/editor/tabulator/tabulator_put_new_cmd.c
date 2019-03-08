/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator_put_new_cmd.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 22:13:29 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 20:51:22 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	add_quote_to_data(t_tab *tabu)
{
	char *tmp;

	tmp = ft_strdup("'");
	ft_strjoin_free(&tmp, tabu->elem->d_name);
	ft_strjoin_free(&tmp, "'");
	ft_strdel(&tabu->elem->d_name);
	tabu->elem->d_name = tmp;
	ft_strdel(&tabu->data);
	tabu->data = ft_strdup(tabu->elem->d_name);
}

void	tabulator_put_new_cmd_next(t_editor *ed, char **new)
{
	int	tmp_pos;

	tmp_pos = ft_strlen(*new);
	ft_strjoin_free(new, ed->hist->cmd + ed->cursor_str_pos);
	go_to_begin_of_line(ed);
	ft_putstr("\E[J");
	ft_strdel(&ed->hist->cmd);
	ed->hist->cmd = *new;
	print_line(ed->hist->cmd, 0, ed->first_char, ed->ws_col);
	ed->cursor_str_pos = ft_strlen(*new);
	ed->last_char = last_char_pos(ed);
	ed->cur_col = ed->last_char;
	calculate_first_and_last_row(ed);
	ed->cur_row = ed->last_row;
	while (ed->cursor_str_pos > tmp_pos)
		move_cursor_left(ed);
}

void	tabulator_put_new_cmd(t_tab *tabu, t_editor *ed)
{
	DIR		*dir;
	char	*new;

	new = ft_strsub(ed->hist->cmd, 0, tabu->start);
	if (tabu->comp)
		if (tabu->mode == 3)
			ft_strjoin_free(&tabu->data, tabu->comp +
			ft_strlen(tabu->path + (tabu->path[1] == '{' ? 2 : 1)));
		else
			ft_strjoin_free(&tabu->data, tabu->comp + ft_strlen(tabu->data));
	else if (check_if_name_with_new_line(tabu->elem->d_name))
		add_quote_to_data(tabu);
	else
		ft_strjoin_free(&tabu->data, tabu->elem->d_name
		+ ft_strlen(tabu->mode == 3 ? tabu->path : tabu->data));
	ft_strjoin_free(&tabu->path, tabu->data);
	check_data_with_space_after(&new, tabu->path);
	tabu->home ? ft_strjoin_free(&tabu->home, tabu->path + 1) : 0;
	if ((tabu->nb_node == 1 && (S_ISDIR(tabu->elem->st_mode) ||
	((dir = opendir(tabu->home ? tabu->home : tabu->path)) && !closedir(dir)))))
		ft_strjoin_free(&new, "/");
	else if (tabu->nb_node == 1 &&
	!ft_strlen(ed->hist->cmd + ed->cursor_str_pos))
		ft_strjoin_free(&new, " ");
	tabulator_put_new_cmd_next(ed, &new);
}
