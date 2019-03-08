/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_from_cursor_to_end.c                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 14:58:15 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/20 07:42:07 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void			delete_from_cursor_to_end(t_editor *ed)
{
	char *tmp;

	ft_strdel(&ed->clipboard);
	ft_putstr("\E[0J");
	tmp = ft_strsub(ed->hist->cmd, 0,
	ft_strlen(ed->hist->cmd) - ft_strlen(ed->hist->cmd + ed->cursor_str_pos));
	ed->clipboard = ft_strdup(ed->hist->cmd + ed->cursor_str_pos);
	ft_strdel(&(ed->hist->cmd));
	ed->hist->cmd = ft_strdup(tmp);
	ed->last_char = ed->cur_col;
	ed->last_row = ed->cur_row;
	ed->cursor_str_pos = ft_strlen(ed->hist->cmd);
}
