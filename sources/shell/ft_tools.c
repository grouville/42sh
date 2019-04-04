/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tools.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/11 01:53:07 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/16 08:23:05 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		ft_isfile(char *file_path)
{
	struct stat		t_stat;

	if (lstat(file_path, &t_stat) != -1 && S_ISREG(t_stat.st_mode))
		return (1);
	else
		return (0);
}

int		ft_isdir(char *path)
{
	struct stat		t_stat;

	if (lstat(path, &t_stat) != -1 && (S_ISDIR(t_stat.st_mode) ||
										S_ISLNK(t_stat.st_mode)))
		return (1);
	else
		return (0);
}

int		ft_read_file(char *filename, char **file_content)
{
	int		fd;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;
	size_t	ret_read;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (0);
	ft_strdel(file_content);
	if (!(*file_content = malloc(sizeof(char))))
		return (0);
	(*file_content)[0] = '\0';
	while ((ret_read = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret_read] = '\0';
		tmp = *file_content;
		*file_content = ft_strnew(ft_strlen(*file_content) + ret_read + 1);
		ft_strcpy(*file_content, tmp);
		ft_strcat(*file_content, buf);
		ft_strdel(&tmp);
	}
	close(fd);
	return (ft_strlen(*file_content));
}

/*
** Découpe le mot word dans str commençant à l'indice i.
** Join les 2 morceaux de str sans word.
** Retourne word malloc.
*/

char 	*ft_strcutword(char **str, int i, int len_word)
{
	char	*aft;
	char	*bfr;
	char 	*ret;
	size_t	len;

	if (!*str || len_word == 0)
		return (NULL);
	ft_strncpy(ret = ft_strnew((size_t)len_word), *str + i, (size_t)len_word);
	len = (size_t)ft_strlen(*str);
	(*str)[i] = '\0';
	bfr = ft_strdup(*str);
	aft = ft_strdup(*str + i + len_word);
	ft_bzero(*str, len);
	ft_strdel(str);
	*str = ft_strjoin(bfr, aft);
	ft_strdel(&bfr);
	ft_strdel(&aft);
	return (ret);
}
