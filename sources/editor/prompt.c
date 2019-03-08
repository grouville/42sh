/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 23:22:07 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/01 21:55:20 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Include/shell.h"

char			*cut_pwd_dir(char *pwd)
{
	int i;

	i = ft_strlen(pwd);
	if (pwd[0] == '/' && i == 1)
		return (pwd);
	while (i >= 0)
	{
		if (pwd[i] == '/')
			return (pwd + i + 1);
		i--;
	}
	return (0);
}

static int		ft_putstrlen(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

static int		prompt_type(t_prompt prompt)
{
	if (prompt == B_QUOTE)
		return (ft_putstrlen("bquote> "));
	else if (prompt == S_QUOTE)
		return (ft_putstrlen("quote> "));
	else if (prompt == D_QUOTE)
		return (ft_putstrlen("dquote> "));
	else if (prompt == HRDC)
		return (ft_putstrlen("heredoc> "));
	return (0);
}

char			*get_user_name(void)
{
	DIR				*dir;
	uid_t			uid;
	char			*full_path;
	struct stat		buf;
	struct dirent	*dirent;

	uid = getuid();
	if ((dir = opendir("/Users")))
	{
		while ((dirent = readdir(dir)))
		{
			full_path = build_full_path("/Users", dirent->d_name);
			if (full_path && !lstat(full_path, &buf)
			&& buf.st_uid == uid && !closedir(dir))
				return (full_path);
			ft_strdel(&full_path);
		}
		closedir(dir);
	}
	return (0);
}

int				display_prompt(t_prompt prompt)
{
	char			*user;
	int				len;
	struct utsname	buf;

	if (prompt != PROMPT)
		return (prompt_type(prompt));
	if ((user = get_user_name()))
		len = ft_putstrlen(cut_pwd_dir(user));
	else
		len = 0;
	if (!uname(&buf))
	{
		if (user)
		{
			len += ft_putstrlen("@");
			ft_strdel(&user);
		}
		len += ft_putstrlen(buf.nodename);
	}
	else if (user)
		ft_strdel(&user);
	len += ft_putstrlen("$ ");
	return (len);
}
