/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator_put_row.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/28 11:32:28 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 15:50:09 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	tabulator_put_color(t_tab_elem *el)
{
	int i;

	i = -1;
	if (el->d_type == 10)
		ft_putstr(BLUE);
	else if (el->d_type == 2 || el->d_type == 6)
		ft_putstr(YEL);
	else if (el->d_type == 8 && el->st_mode && (el->st_mode & S_IXUSR))
		ft_putstr(GREEN);
	else if (el->d_type == 4 || (el->path && S_ISDIR(el->st_mode)))
		ft_putstr(RED);
	if (check_if_name_with_new_line(el->d_name))
		while (el->d_name[++i])
			write(1, el->d_name[i] == '\n' ? "?" : &(el->d_name)[i], 1);
	else
		ft_putstr(el->d_name);
	ft_putstr(END);
}

void	tabulator_put_type(t_tab_elem *el)
{
	if (el->d_type == 2)
		ft_putchar('%');
	else if (el->d_type == 6)
		ft_putchar('#');
	else if (el->d_type == 10)
		ft_putchar('@');
	else if (el->d_type == 8 && el->st_mode && (el->st_mode & S_IXUSR))
		ft_putchar('*');
	else if (el->d_type == 4 ||
	(el->path && (S_ISDIR(el->st_mode))))
		ft_putchar('/');
	else
		ft_putchar(' ');
}

void	tabulator_put_elem(t_tab_elem *list, int index, t_tab *ta, int cur_col)
{
	int				i;
	int				j;
	unsigned long	space;

	i = 0;
	j = 0;
	while (list && i != index)
	{
		list = list->next;
		i++;
	}
	if (list)
	{
		tabulator_put_color(list);
		tabulator_put_type(list);
		space = ft_strlen(list->d_name);
	}
	while (list && cur_col < ta->nb_col - 1 && space++ < ta->max_len + 1)
		ft_putchar(' ');
}

void	tabulator_one_row(t_tab_elem *elem, int max_len)
{
	int i;

	i = 0;
	while (elem)
	{
		tabulator_put_color(elem);
		tabulator_put_type(elem);
		i++;
		tputs(tgoto(tgetstr("ch", NULL), 0, i *
		(max_len + 2)), 1, ft_putchar);
		elem = elem->next;
	}
	write(1, "\n", 1);
}

int		tabulator_multi_row(t_tab *tabu, t_editor *ed)
{
	int i;
	int n;
	int ret;

	if (tabu->nb_row > (int)ed->ws_row &&
	((!(ret = tabulator_read(tabu, ed, 0)) || ret == -1 || ret == -3)))
		return (ret);
	n = -1;
	while (++n < tabu->nb_row && !(i = 0))
	{
		if (n + 1 >= ed->ws_row &&
		(((ret = tabulator_read(tabu, ed, 1)) == -1 || ret == -3)))
			return (ret);
		while (tabu->nb_row && i < tabu->nb_col
		&& (n + (i * tabu->nb_row)) <= tabu->nb_node)
		{
			tabulator_put_elem(tabu->elem, n + (i * tabu->nb_row), tabu, i);
			i++;
			tabu->nb_node++;
		}
		write(1, "\n", 1);
	}
	return (1);
}
