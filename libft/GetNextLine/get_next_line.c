/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 17:31:26 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/04 16:12:40 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** clean_exit si read == -1 || buf de read == '\0'
*/

int			ft_clean_exit(int err, char **str)
{
	ft_strdel(str);
	return (err);
}

static int	ft_read_file(char **str, int fd)
{
	char	*buf;
	int		ret;

	buf = ft_strnew(BUFF_SIZE);
	ret = read(fd, buf, BUFF_SIZE);
	if (ret > 0)
	{
		buf[ret] = '\0';
		*str = ft_strcat_free(*str, buf);
	}
	free(buf);
	return (ret);
}

int			get_next_line(const int fd, char **line)
{
	static char	*str = NULL;
	char		*tmp;
	int			ret;
	char		*free_str;

	if (!(line) || BUFF_SIZE < 0 || fd < 0 || (!str && !(str = ft_strnew(0))))
		return (-1);
	while (!(tmp = ft_strchr(str, '\n')))
	{
		ret = ft_read_file(&str, fd);
		if ((ret == 0 && !(ft_strlen(str))) || ret == -1)
			return (ft_clean_exit(ret, &str));
		if (ret == 0)
			str = ft_strjoin(str, "\n");
	}
	free_str = str;
	*line = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(tmp));
	if (tmp && *(tmp + 1) != '\0')
		str = ft_strdup(++tmp);
	else
		str = NULL;
	ft_strdel(&free_str);
	return (1);
}
