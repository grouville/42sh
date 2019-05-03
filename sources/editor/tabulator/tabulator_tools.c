/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator_tools.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/01 23:43:13 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 07:57:18 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

char	*build_full_path(char *path, char *d_name)
{
	char *full_path;

	if (path && path[0] == '~')
	{
		if (path[1] == '/')
			full_path = get_user_name();
		else
			full_path = ft_strdup("/Users/");
		if (!full_path)
			return (NULL);
		ft_strjoin_free(&full_path, path + 1);
	}
	else
		full_path = ft_strdup(path);
	if (full_path && full_path[ft_strlen(full_path) - 1] != '/')
		ft_strjoin_free(&full_path, "/");
	ft_strjoin_free(&full_path, d_name);
	return (full_path);
}

void	free_tab(t_tab *tabu)
{
	t_tab_elem *tmp;

	ft_strdel(&tabu->path);
	ft_strdel(&tabu->data);
	ft_strdel(&tabu->comp);
	ft_strdel(&tabu->home);
	if (tabu->dir)
		closedir(tabu->dir);
	while (tabu->elem)
	{
		tmp = tabu->elem->next;
		ft_strdel(&tabu->elem->d_name);
		ft_strdel(&tabu->elem->path);
		free(tabu->elem);
		tabu->elem = tmp;
	}
	free(tabu);
}

int		term_tabulator_enough_space(t_editor *ed, t_tab *tabu)
{
	int new_line_pos;

	new_line_pos = check_if_new_line_in_line(ed);
	if ((ft_strlen(ed->hist->cmd) + ed->prompt_size +
	ft_strlen(tabu->elem->d_name)) >= (ed->ws_col * ed->ws_row) ||
	((ed->first_row == 1 && ed->last_row == ed->ws_row) &&
	(new_line_pos > -1 ? new_line_pos : ed->last_char)
	+ (ft_strlen(tabu->elem->d_name) - 1) >= ed->ws_col))
		return (0);
	return (1);
}
