/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_check_expansions.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 15:21:29 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 21:57:32 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

char	*expansions_build_event(char *str)
{
	int end;
	int start;

	end = 0;
	start = 0;
	while (str && str[end])
	{
		if (!start && (str)[end] == '!')
			start = end + 1;
		else if (start && (str[end] == ' ' || str[end] == '"' ||
					str[end] == '!'))
		{
			if (str[end] == '!')
				end++;
			break ;
		}
		end++;
	}
	return (!(end - start) ? NULL : ft_strsub(str, start, end - start));
}

int		check_expansions_mode(char *str)
{
	int mode;

	mode = 0;
	if (ft_isdigit((str)[0]))
		mode = 1;
	if ((str)[0] == '-')
	{
		if ((str)[1])
		{
			if (ft_isdigit((str)[1]))
				mode = 2;
			else if (ft_isalpha((str)[1]))
				mode = 3;
		}
	}
	if (str[0] == '!')
		mode = 4;
	return (mode);
}

int		check_expansions_new_cmd(t_shell *shell, int i, char **event, char *cmd)
{
	char	*add;
	char	*new;
	char	*nb;
	int		len;

	new = NULL;
	add = *event + ((*event)[1] == '-' ? 1 : 0);
	nb = ft_itoa(ft_atoi(add));
	if (i)
		new = ft_strsub(shell->str, 0, i);
	ft_strjoin_free(&new, cmd);
	len = ft_strlen(new);
	ft_strjoin_free(&new, shell->str + (i + ft_strlen(*event) + 1));
	if (ft_atoi(nb))
		ft_strjoin_free(&new, add + ft_strlen(nb));
	ft_strdel(&shell->str);
	ft_strdel(&nb);
	shell->str = new;
	ft_strdel(event);
	return (len);
}

BOOL	expansions_add_event(t_shell *shell, int i)
{
	int		mode;
	int		nb;
	char	*event;
	t_data	*tmp;

	nb = 0;
	tmp = shell->hist;
	event = expansions_build_event(shell->str);
	mode = check_expansions_mode(event);
	while (tmp)
	{
		if (tmp->cmd && ((((!mode || mode == 3) && (!ft_strncmp(tmp->cmd, event
		+ (!mode ? 0 : 1), ft_strlen(event + (!mode ? 0 : 1))))) || (mode == 4
		&& nb == 1)) || (mode == 1 && tmp->nb == ft_atoi(event)) || (mode == 2
		&& nb == ft_atoi(event + 1))))
			return (check_expansions_new_cmd(shell, i, &event, tmp->cmd));
		nb++;
		tmp = tmp->prev;
	}
	ft_dprintf(2, "42sh: %s: event not found\n", event);
	ft_strdel(&event);
	return (-1);
}

BOOL	check_expansions(t_shell *shell)
{
	int d[3];

	ft_bzero(d, sizeof(d));
	while (shell->str && shell->str[d[0]])
	{
		if (shell->str[d[0]] == '\\' &&
		ft_strlen(shell->str) >= (d[0] + 2) && d[1] != '\'')
			d[0] += 2;
		if (ft_strchr("'\"", shell->str[d[0]]) && d[1] == 0)
			d[1] = shell->str[d[0]];
		else if (shell->str[d[0]] == d[1] && d[1] != 0)
			d[1] = 0;
		if (shell->str[d[0]] == '!' && shell->str[d[0] + 1] != '\"' &&
		shell->str[d[0] + 1] != ' ' && shell->str[d[0] + 1] && d[1] != '\'')
		{
			d[2] = 1;
			if ((d[0] = expansions_add_event(shell, d[0])) == -1)
				return (1);
			continue ;
		}
		d[0] += (shell->str[d[0]] ? 1 : 0);
	}
	if (d[2])
		ft_putendl(shell->str);
	return (0);
}
