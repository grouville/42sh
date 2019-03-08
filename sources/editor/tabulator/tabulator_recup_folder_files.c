/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator_recup_folder_files.c                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/28 12:09:31 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/01 21:54:16 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	tabulator_autocomplete(char **comp, char *d_name)
{
	int i;

	i = 0;
	if (!(*comp))
	{
		*comp = ft_strdup(d_name);
		return ;
	}
	while ((*comp)[i] && d_name[i] && (*comp)[i] == d_name[i])
		i++;
	ft_strdel(comp);
	*comp = ft_strsub(d_name, 0, i);
}

int		check_if_true_file(t_tab *tabu, t_dirent *dir, char *bin)
{
	if ((((!tabu->data && ft_strcmp(".", dir->d_name) &&
	ft_strcmp("..", dir->d_name))) || (((bin &&
	ft_strcmp(".", dir->d_name) && ft_strcmp("..", dir->d_name)) || !bin)
	&& tabu->data && !ft_strncmp(dir->d_name, tabu->data,
	ft_strlen(tabu->data)))) && tabulator_check_executable(tabu, dir, bin))
		return (1);
	return (0);
}

void	tabulator_fill_list(t_tab *ta, struct dirent *dir,
		t_tab_elem **list, char *bin)
{
	t_stat			buf;
	t_tab_elem		*new;

	if (!ta->comp || ft_strlen(ta->comp))
		tabulator_autocomplete(&ta->comp, dir->d_name);
	ta->max_len = dir->d_namlen > ta->max_len ? dir->d_namlen : ta->max_len;
	if (!(new = malloc(sizeof(t_tab_elem))))
		return ;
	new->d_name = ft_strdup(dir->d_name);
	new->path = build_full_path(bin ? bin : ta->path, dir->d_name);
	lstat(new->path, &buf);
	new->st_mode = buf.st_mode;
	new->d_namlen = dir->d_namlen;
	new->d_type = dir->d_type;
	new->next = NULL;
	new->prev = NULL;
	if (*list)
	{
		(*list)->next = new;
		new->prev = *list;
	}
	*list = new;
	ta->elem = !ta->elem ? new : ta->elem;
	ta->nb_node++;
}

void	tabulator_recup_folder_files(t_tab *tabu, char *bin)
{
	struct dirent	*dir;
	t_tab_elem		*list;

	list = tabu->last_elem;
	while ((dir = readdir(tabu->dir)))
		if (check_if_true_file(tabu, dir, bin))
			tabulator_fill_list(tabu, dir, &list, bin);
	tabu->last_elem = list;
	closedir((tabu->dir));
	tabu->dir = NULL;
}
