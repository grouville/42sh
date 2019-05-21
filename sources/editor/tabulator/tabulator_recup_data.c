/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator_recup_data.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/28 12:00:36 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/01 18:18:28 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	tabulator_sort_list(t_tab_elem **list)
{
	t_tab_elem *tmp;

	while ((*list) && (*list)->next)
	{
		if (ft_strcmp((*list)->d_name, (*list)->next->d_name) > 0)
		{
			tmp = *list;
			*list = (*list)->next;
			tmp->next = (*list)->next;
			if (tmp->next)
				tmp->next->prev = tmp;
			(*list)->prev = tmp->prev;
			tmp->prev = *list;
			(*list)->next = tmp;
			if ((*list)->prev)
				(*list)->prev->next = *list;
			if ((*list)->prev)
				*list = (*list)->prev;
		}
		else
			*list = (*list)->next;
	}
	while ((*list) && (*list)->prev)
		*list = (*list)->prev;
}

void	check_home(t_tab *tabu)
{
	char *tmp;

	if (tabu->path[1] == '/')
		tabu->home = get_user_name();
	else
		tabu->home = ft_strdup("/Users/");
	if (tabu->home)
	{
		tmp = ft_strdup(tabu->home);
		ft_strjoin_free(&tmp, tabu->path + 1);
		ft_strdel(&tabu->path);
		tabu->path = tmp;
	}
}

int		tabulator_open_dir(t_tab *tabu)
{
	int		len;
	char	*tmp;

	if (tabu->path[0] == '~')
		check_home(tabu);
	len = ft_strlen(tabu->path) + 1;
	while (--len)
	{
		tmp = ft_strsub(tabu->path, 0, len);
		if (tmp && tmp[len - 1] == '/' && (tabu->dir = opendir(tmp)))
		{
			tabu->data = ft_strlen(tabu->path + len) ? ft_strdup(tabu->
			path + len) : tabu->data;
			ft_strdel(&tabu->path);
			tabu->path = tabu->home ? ft_strdup("~") : ft_strdup(tmp);
			if (tabu->home)
				ft_strjoin_free(&tabu->path, tmp + ft_strlen(tabu->home));
			ft_strdel(&tmp);
			return (1);
		}
		ft_strdel(&tmp);
	}
	tabu->data = ft_strdup(tabu->path);
	ft_strdel(&tabu->path);
	return (0);
}

void	tabulator_get_binairies(t_tab *tabu)
{
	int		i;
	char	*b_path;
	char	**bin;

	i = -1;
	if (!(b_path = get_envp(check_if_env_var_existing(tabu->env, "PATH") ?
	tabu->env : tabu->envl, "PATH")))
		return ;
	if (!(bin = ft_strsplit(b_path, ':')))
		return ;
	while (bin && bin[++i])
	{
		if ((tabu->dir = opendir(bin[i])))
			tabulator_recup_folder_files(tabu, bin[i]);
		ft_strdel(&(bin[i]));
	}
	ft_strdel(&(bin[i]));
	free(bin);
}

void	tabulator_recup_data(t_editor *ed, t_tab *tabu)
{
	tabu->save_pos = ed->cursor_str_pos;
	if (!(tabu->mode = tabulator_get_path(ed, tabu)))
		tabulator_get_binairies(tabu);
	else if (tabu->mode == 1 || tabu->mode == 2)
	{
		if (tabu->path)
			check_data_with_space_before(&tabu->path);
		if (tabu->path && !(tabulator_open_dir(tabu)) && tabu->mode == 1)
			tabulator_get_binairies(tabu);
		if (tabu->dir || (tabu->dir = opendir(".")))
			tabulator_recup_folder_files(tabu, NULL);
	}
	else if (tabu->mode == 3)
		tabulator_check_if_var(tabu);
	if (!(tabu->nb_col = (ed->ws_col) / (tabu->max_len + 2)))
		tabu->nb_col = 1;
	tabu->nb_row = tabu->nb_node / tabu->nb_col;
	tabulator_sort_list(&tabu->elem);
	while (tabu->nb_row && (tabu->nb_row * tabu->nb_col) < tabu->nb_node)
		tabu->nb_row++;
	if (tabu->comp && (tabu->nb_node == 1 ||
	ft_strlen(tabu->comp) == ft_strlen(tabu->data) || (tabu->mode == 3 &&
	ft_strlen(tabu->comp) ==
	ft_strlen(tabu->path + (tabu->path[1] == '{' ? 2 : 1)))))
		ft_strdel(&tabu->comp);
}
