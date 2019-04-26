/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/23 13:13:48 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 02:11:10 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
*** - Aim of the function :
*** - Retrieve the corresponding job, or print error if doesn't exist
*/

int         job_percentage_number_exists_or_not_bg(char *cmd, int nb,
                t_job **job)
{
    t_job   *j;
    int		nb_bgjob;

    nb_bgjob = 1;
    j = getter_job()->first_job;
    while (j)
    {
        if (j->num == nb)
            break ;
        j = j->next;
    }
    if (j && nb != 0)
        *job = j;
    else
    {
        ft_dprintf(2, nb == 0 ? "bash: bg: current: no such job\n"
            : "bash: bg: %s: no such job\n", cmd);
        *job = NULL;
        return (1);
    }
    return (0);
}

/*
*** - Aim of the function
*** - Check if job exists
*** - Under the form of < 123 >, a number
*** - Or : < %X >, "%" followed by a number
*** - If yes, we assign job to the corresponding pgid
*/

int             check_if_job_exists_bg(char *cmd, t_job **j)
{
    if (!is_number(cmd))
        return (job_percentage_number_exists_or_not_bg(cmd,
            ft_atoi(cmd), j));
    else if (*cmd == '%' && !is_number(cmd + 1))
        return (job_percentage_number_exists_or_not_bg(cmd,
            ft_atoi(cmd + 1), j));
    else
    {
        ft_dprintf(2, "bash: fg: %s: no such job\n", cmd);
        return (1);
    }
    return (0);
}

/*
*** - Aim of the function :
*** - Manage the bg builtin
*/

int			    ft_builtin_bg(char **cmd)
{
    t_job   *j;
    int     job_number;
    int     i;
    int     ret;

    i = 1;
    ret = 0;
    if (ft_arrlen(cmd) == 1)
    {
        job_number = find_last_job_put_in_background();
        if (job_percentage_number_exists_or_not_bg(*cmd,
            job_number, &j))
            ret = 1;
        if (j)
        	put_job_in_background(j, job_is_stopped(j) ? 1 : 0);
    }
    else
    {
        while (cmd[i])
        {
            if (check_usage(cmd[i]) && (i++) && (ret = 2))
                continue ;
            if (check_if_job_exists_bg(cmd[i], &j) && (i++) && (ret = 1))
                continue ;
            put_job_in_background(j, job_is_stopped(j) ? 1 : 0);
            i++;
        }
    }
    return (0);
}