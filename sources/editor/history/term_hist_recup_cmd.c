/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recup_hist_from_file.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/03 14:29:35 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 15:28:50 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void		fill_hist_file(t_data *hist, char *file)
{
	t_data		*tmp;
	int			fd;

	if ((fd = open(file, O_WRONLY | O_CREAT |
	O_APPEND | O_TRUNC, 0644)) < 0)
		return ;
	while (hist->prev)
		hist = hist->prev;
	while (hist)
	{
		if (hist->cmd)
		{
			write(fd, hist->cmd, ft_strlen(hist->cmd));
			ft_strdel(&hist->cmd);
			write(fd, "\n", 1);
		}
		tmp = hist->next;
		free(hist);
		hist = tmp;
	}
	free(hist);
	close(fd);
}

t_data		*recup_hist_from_file(t_data *hist, char *file)
{
	char	c;
	int		i;
	int		j;

	c = 0;
	i = 0;
	j = -1;
	while (file && file[i])
	{
		if (j != -1 && file[i] == '\n' && c == 0)
		{
			hist->cmd = ft_strsub(file, j, i - j);
			hist = hist_add(hist);
			j = -1;
		}
		if (j == -1 && ft_isprint(file[i]))
			j = i;
		if (((file[i] == '\'' || file[i] == '\"' || file[i] == '`') && c == 0)
			|| ((c == '\'' && file[i] == '\'') || (c == '\"' && file[i] == '\"')
			|| (c == '`' && file[i] == '`')))
			c = c ? 0 : file[i];
		i++;
	}
	return (hist);
}

t_data		*hist_add(t_data *hist)
{
	t_data *new;
	t_data *now;

	new = NULL;
	now = NULL;
	if (!(new = malloc(sizeof(t_data))))
		exit(EXIT_FAILURE);
	ft_bzero(new, sizeof(t_data));
	new->nb = hist->nb + 1;
	hist->next = new;
	now = hist;
	hist = new;
	hist->prev = now;
	return (new);
}

t_data		*init_hist(char *file)
{
	t_data		*hist;
	char		*file_str;
	int			fd;
	int			ret;

	if (!(hist = malloc(sizeof(t_data))))
		exit(EXIT_FAILURE);
	ft_bzero(hist, sizeof(t_data));
	hist->nb = 1;
	file_str = NULL;
	ret = 0;
	if (!access(file, R_OK | F_OK))
		if ((fd = open(file, O_RDONLY)))
		{
			if ((ret = get_read_key(fd, &file_str)))
			{
				hist = recup_hist_from_file(hist, file_str);
				ft_strdel(&file_str);
			}
			close(fd);
		}
	if (ret == -1)
		return (NULL);
	return (hist);
}
