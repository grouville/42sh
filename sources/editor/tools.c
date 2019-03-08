/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/17 21:17:16 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/22 19:07:20 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	calculate_first_and_last_row(t_editor *ed)
{
	int nb_l;

	if ((ed->first_row +
	(nb_l = nb_line(ed->hist->cmd, ed->first_char, ed->ws_col))) > ed->ws_row)
	{
		ed->last_row = ed->ws_row;
		ed->first_row = ed->last_row - nb_l;
	}
	else
		ed->last_row = ed->first_row + nb_l;
}

int		nb_line(char *line, int first_char, int ws_col)
{
	int i;
	int pos;
	int row;

	i = 0;
	pos = first_char;
	row = 0;
	while (line && line[i])
	{
		if (pos == ws_col || line[i] == '\n')
		{
			pos = 0;
			row++;
		}
		pos++;
		i++;
	}
	return (row);
}

void	print_line(char *line, int str_pos, int cur_pos, int ws_col)
{
	while (line && line[str_pos])
	{
		if (line[str_pos] != '\n')
			ft_putchar(line[str_pos]);
		if (line[str_pos] == '\n' || cur_pos == ws_col)
		{
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
			tputs(tgetstr("cr", NULL), 1, ft_putchar);
			cur_pos = 1;
		}
		else
			cur_pos++;
		str_pos++;
	}
}

int		enough_space_on_screen(t_editor *ed)
{
	int str_len;
	int new_line_pos;

	str_len = (CTRL_P ? ft_strlen(ed->clipboard) : ft_strlen(ed->key)) - 1;
	new_line_pos = check_if_new_line_in_line(ed);
	if (((ft_strlen(ed->hist->cmd) + ed->prompt_size + str_len))
	>= (ed->ws_col * ed->ws_row) ||
	((ed->first_row == 1 && ed->last_row == ed->ws_row) &&
	((new_line_pos > -1 ? new_line_pos : ed->last_char)
	+ str_len >= ed->ws_col)) ||
	(nb_line(ed->hist->cmd, ed->first_char, ed->ws_col) +
	nb_line(CTRL_P ? ed->clipboard : ed->key, ed->last_char,
	ed->ws_col) > ed->ws_row) || (ed->first_row
	== 1 && ed->last_row == ed->ws_row && ed->cur_row == ed->ws_row &&
	(ed->last_char + str_len) >= ed->ws_col))
		return (0);
	return (1);
}

int		get_read_key(int fd, char **key)
{
	int		ret;
	char	buf[BUFF_READ + 1];

	ret = 0;
	if (BUFF_READ < 1)
		return (-1);
	ft_bzero(buf, BUFF_READ + 1);
	if ((ret = read(fd, buf, BUFF_READ)))
	{
		buf[ret] = '\0';
		if (!ft_strjoin_free(key, buf))
			return (-1);
	}
	if (ret == BUFF_READ)
		get_read_key(fd, key);
	return (ret);
}
