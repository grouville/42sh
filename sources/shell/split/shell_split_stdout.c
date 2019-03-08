/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_split_stdout.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/22 00:38:38 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/22 00:38:38 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** redi_from peut être un fd sur plusieurs chiffre, on rev pour le atoi
*/

int			get_stdout_from(char *redi, int pos)
{
	char	*rev;
	char	*redi_from;
	int		i;

	if (pos == 0)
		return (1);
	i = 0;
	while (i < pos)
	{
		if (!(ft_isdigit(redi[i++])))
			return (1);
	}
	rev = ft_strrev(ft_strdup(redi));
	pos = ft_strlen(redi) - pos;
	redi_from = ft_strsub(rev, (unsigned)pos, (size_t)ft_strlen(rev) - pos);
	ft_strdel(&rev);
	i = ft_atoi(ft_strrev(redi_from));
	ft_strdel(&redi_from);
	return (i);
}

/*
** tronque {arg} si {from} n'a pas que des digits
*/

void		shell_get_stdout(char **arg, int *i, t_output *redi)
{
	redi->from = get_stdout_from(*arg, *i);
	ft_strdel(&redi->to);
	if ((*arg)[*i] && (*arg)[*i + 1] == '>')
	{
		redi->append = 1;
		(*arg)[*i] = '\0';
		*i += 2;
		redi->to = get_stdout_to(*arg, *i);
	}
	else if ((*arg)[*i])
	{
		redi->append = 0;
		(*arg)[*i] = '\0';
		*i += 1;
		redi->to = get_stdout_to(*arg, *i);
	}
}

t_output	*add_stdout(t_output **first_redi)
{
	t_output	*new_redi;
	t_output	*t_next;

	if (!(new_redi = malloc(sizeof(t_output))))
		exit(EXIT_FAILURE);
	new_redi->append = 0;
	new_redi->from = 1;
	new_redi->to = ft_strdup("&1");
	new_redi->next = NULL;
	if (!(*first_redi))
	{
		new_redi->start = new_redi;
		*first_redi = new_redi;
	}
	else
	{
		new_redi->start = *first_redi;
		t_next = *first_redi;
		while (t_next->next != NULL)
			t_next = t_next->next;
		t_next->next = new_redi;
	}
	return (new_redi);
}

int			shell_stdout_sub(char **arg, int pos, t_output *redi)
{
	int		len;
	char	*tmp;
	char	*bfr;
	char	*aft;

	len = len_stdout_to(*arg + pos);
	if (*arg && ft_atoi(*arg) == redi->from)
	{
		tmp = ft_strsub(*arg + pos, (uint)len, ft_strlen(*arg + pos + len));
		ft_strdel(arg);
		*arg = tmp;
		pos = 0;
	}
	else
	{
		bfr = ft_strdup(*arg);
		aft = ft_strdup(*arg + pos + len);
		ft_strdel(arg);
		*arg = ft_strjoin(bfr, aft);
		pos = ft_strlen(bfr);
		ft_strdel(&bfr);
		ft_strdel(&aft);
	}
	return (pos);
}

/*
** shell redi peut renvoyer NULL si malloc fail.
** On effectue un exit propre (à faire).
*/

t_output	*shell_std_out(char **arg, t_output **first_redi, char quote)
{
	int			i;
	t_output	*redi;

	if (*first_redi && (get_last_stdout(*first_redi))->to == NULL && *arg)
		*arg = complete_stdout_to(arg, get_last_stdout(*first_redi));
	redi = NULL;
	i = (quote == ' ') ? 0 : 1;
	while (*arg && (*arg)[i])
	{
		if ((*arg)[i] == '\\' && ft_strlen(*arg) >= (i + 2) && quote != '\'')
			i += 2;
		if (ft_strchr("'\"", (*arg)[i]) && quote == ' ')
			quote = (*arg)[i];
		else if ((*arg)[i] == quote && quote != ' ')
			quote = ' ';
		if ((*arg)[i] == '>' && quote == ' ')
		{
			redi = add_stdout(first_redi);
			shell_get_stdout(arg, &i, redi);
			i = shell_stdout_sub(arg, i, redi);
		}
		else
			i += ((*arg)[i]) ? 1 : 0;
	}
	return (*first_redi);
}
