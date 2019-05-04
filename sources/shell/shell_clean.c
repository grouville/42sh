/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_clean.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/23 20:20:21 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/23 20:20:21 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	clean_arr_mlti(char **arr)
{
	int i;

	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		if ((int)arr[i] == -1 || (int)arr[i] == -2 || (int)arr[i] == -3)
			arr[i++] = NULL;
		else
			ft_strdel(&arr[i++]);
	}
	if (arr != NULL)
		free(arr);
}

void	clean_redi(t_output **redi)
{
	t_output	*tmp;

	while ((*redi)->next != NULL)
	{
		tmp = *redi;
		(*redi) = (*redi)->next;
		ft_strdel(&tmp->to);
		free(tmp);
	}
	ft_strdel(&(*redi)->to);
	free(*redi);
}

int		clean_jobs(t_job **jobs)
{
	t_job	*prev;

	if (*jobs)
	{
		prev = *jobs;
		while ((*jobs = (*jobs)->next))
		{
			free(prev);
			prev = *jobs;
		}
		free(prev);
		*jobs = NULL;
	}
	return (-1);
}

int		shell_clean_data(t_cmd **cmd, t_shell *shell, BOOL hrdc_tmp)
{
	t_cmd *start;

	start = (*cmd)->start;
	clean_cmd(&(*cmd)->start->next_cmd);
	free(start);
	*cmd = NULL;
	ft_strdel(&shell->str);
	if (hrdc_tmp)
		ft_strdel(&shell->hrdc_tmp);
	return (1);
}

void		clean_jobs_all(void)
{
	t_job	*curr;
	t_job	*tmp;
	t_js	*jsig;

	jsig = getter_job();
	curr = jsig->first_job->next;
	tmp = jsig->first_job;
	while (curr)
	{
		tmp = curr->next;
		free_job(&curr, NULL);
		curr = tmp;
	}
	free(jsig->first_job);
}
