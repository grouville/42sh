/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc_search_occurence.c                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 13:15:39 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 10:26:09 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

static int		builtin_search_occurence_pos(t_fc *fc, t_data *hist, int pos)
{
	t_data	*tmp;
	int		cmd_nb;
	int		nb;
	char	*occurence;

	tmp = hist->prev->prev;
	occurence = !pos ? fc->first : fc->last;
	cmd_nb = -1;
	nb = ft_atoi(occurence);
	if (tmp && ft_isdigit(occurence[occurence[0] == '-' ? 1 : 0]))
	{
		if (nb < 0 && ((nb + 1) + tmp->nb) > 0)
			cmd_nb = (nb + 1) + tmp->nb;
		else if (nb > 0 && nb <= tmp->nb)
			cmd_nb = nb;
	}
	while (!nb && tmp && ((tmp->cmd &&
	ft_strncmp(tmp->cmd, occurence, ft_strlen(occurence))) || !tmp->cmd))
		tmp = tmp->prev;
	if (!nb && tmp)
		cmd_nb = tmp->nb;
	if (cmd_nb == -1)
		ft_putstr_fd("42sh: fc: history specification out of range\n", 2);
	return (cmd_nb);
}

static void		builtin_fc_browse_history_for_occurence(t_fc *fc, int first_nb,
		int last_nb, t_data *hist)
{
	t_data	*tmp;
	int		first;

	tmp = hist;
	first = 0;
	while (tmp)
	{
		if ((!first && first_nb == tmp->nb && (first = 1))
		|| (first && last_nb && first_nb != tmp->nb && last_nb <= tmp->nb))
		{
			if (fc->fd >= 0 && write(fc->fd, tmp->cmd, ft_strlen(tmp->cmd))
			&& write(fc->fd, "\n", 1))
				;
			else
			{
				if (fc->op && ft_strchr(fc->op, 'l') && !ft_strchr(fc->op, 'n'))
					ft_dprintf(1, "%d\t", tmp->nb);
				ft_dprintf(1, "%s\n", tmp->cmd);
			}
		}
		if (first && (!last_nb || first_nb == last_nb ||
		last_nb == tmp->nb))
			break ;
		tmp = first && last_nb > first_nb ? tmp->next : tmp->prev;
	}
}

void			builtin_fc_search_first_and_last(char **args, t_fc *fc)
{
	int nb;

	nb = 0;
	while (args && args[++fc->i] && nb < 2)
	{
		if ((args[fc->i][0] == '-' && ft_isdigit(args[fc->i][1])) ||
				ft_isdigit(args[fc->i][0]))
			!nb ? (fc->first = ft_itoa(ft_atoi(args[fc->i])))
				: (fc->last = ft_itoa(ft_atoi(args[fc->i])));
		else
			!nb ? (fc->first = ft_strdup(args[fc->i]))
				: (fc->last = ft_strdup(args[fc->i]));
		nb++;
	}
	if (!fc->first && fc->op && ft_strchr(fc->op, 'l'))
	{
		fc->first = ft_strdup("-15");
		fc->last = ft_strdup("-1");
	}
	else if (!fc->first)
		fc->first = ft_strdup("-1");
}

void			buitlin_fc_substitution_get_old_new(t_fc *fc)
{
	if (ft_strchr(fc->first, '='))
	{
		fc->old = get_var(fc->first);
		fc->new = get_value(fc->first);
		if (fc->last)
			ft_swap((int*)&fc->first, (int*)&fc->last);
		else
		{
			ft_strdel(&fc->first);
			fc->first = ft_strdup("-1");
		}
	}
	ft_strdel(&fc->last);
}

int				builtin_fc_search_occurence(t_fc *fc, t_data *hist)
{
	int first_nb;
	int last_nb;

	first_nb = 0;
	last_nb = 0;
	if (((first_nb = builtin_search_occurence_pos(fc,
	hist, 0)) != -1) && fc->last && (!fc->op || !ft_strchr(fc->op, 's')))
		last_nb = builtin_search_occurence_pos(fc, hist, 1);
	if (first_nb == -1 || last_nb == -1 || ((!fc->op || (fc->op
	&& (ft_strchr(fc->op, 'e') || ft_strchr(fc->op, 's'))
	&& !ft_strchr(fc->op, 'l'))) &&
	((fc->fd = open("/tmp/.42sh-fc_cmd_list",
	O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644)) < 0)))
		return (1);
	if (first_nb && last_nb && fc->op && ft_strchr(fc->op, 'r'))
		ft_swap(&first_nb, &last_nb);
	builtin_fc_browse_history_for_occurence(fc, first_nb, last_nb, hist);
	if (fc->fd >= 0)
		close(fc->fd);
	return (0);
}
