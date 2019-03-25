/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_check_expansions.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 15:21:29 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 09:04:04 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

char	*expansions_build_event(char *str)
{
	int start;
	int end;
	int first;

	first = 0;
	end = 0;
	start = 0;
	while (str && (str)[end])
	{
		if (!first && (str)[end] == '!' && (first = 1))
			start = end;
		else if (first && (str[end] == ' ' || str[end] == '"' ||
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
	if (ft_isdigit((str)[1]))
		mode = 1;
	if ((str)[1] == '-')
	{
		if ((str)[2])
		{
			if (ft_isdigit((str)[2]))
				mode = 2;
			if (ft_isalpha((str)[2]))
				mode = 3;
		}
	}
	dprintf(2, "str: %s\n", str);
	if (str[0] == '!' && str[1] == '!')
		mode = 4;
	return (mode);
}

void	check_expansions_new_cmd(t_shell *shell, int i, char **event, char *cmd)
{
	char *add;
	char *new;
	char *nb;

	new = NULL;
			dprintf(2, "YAHOUUU0000000000\n");
	add = *event + ((*event)[1] == '-' ? 2 : 1);
			dprintf(2, "YAHOUUU11111111111111111\n");
	nb = ft_itoa(ft_atoi(add));
	if (i)
		new = ft_strsub(shell->str, 0, i);
	dprintf(2, "event: %s\n", *event);
//	if (((*event)[0] == '!' && (*event)[1] == '!') || (*event)[0] != '!')
		ft_strjoin_free(&new, cmd);
	dprintf(2, "new0: %s\n", new);
	ft_strjoin_free(&new, shell->str + i + ft_strlen(*event));
	dprintf(2, "new1: %s\n", new);
	ft_strjoin_free(&new, add + ft_strlen(nb));
	dprintf(2, "new2: %s\n", new);
	ft_strdel(&shell->str);
	ft_strdel(&nb);
	shell->str = new;
	ft_strdel(event);
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
	dprintf(2, "mode: %d\n", mode);
	while (tmp)
	{
		if (tmp->cmd && ((((!mode || mode == 3) && (!ft_strncmp(tmp->cmd, event +
		(!mode ? 1 : 2), ft_strlen(event + (!mode ? 1 : 2))))) || (mode == 4 &&
		nb == 1)) || (mode == 1 && tmp->nb == ft_atoi(event + 1)) || (mode == 2
		&& nb == ft_atoi(event + 2))))
		{
			check_expansions_new_cmd(shell, i, &event, tmp->cmd);
			return (0);
		}
		nb++;
		tmp = tmp->prev;
	}
	ft_dprintf(2, "42sh: %s: event not found\n", event);
	ft_strdel(&event);
	return (1);
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
			if (expansions_add_event(shell, d[0]))
				return (1);
			d[2] = 1;
			continue ;
		}
		d[0] += (shell->str[d[0]] ? 1 : 0);
	}
	if (d[2])
		ft_putendl(shell->str);
	return (0);
}
