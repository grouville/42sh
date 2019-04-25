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
        if (job_percentage_number_exists_or_not(*cmd,
            job_number, &j))
            ret = 1;
        put_job_in_background(j, job_is_stopped(j) ? 1 : 0);
    }
    else
    {
        while (cmd[i])
        {
            printf("i: %d\n", i);
            if (check_usage(cmd[i]) && (i++) && (ret = 2))
                continue ;
            if (check_if_job_exists(cmd[i], &j) && (i++) && (ret = 1))
                continue ;
            put_job_in_background(j, job_is_stopped(j) ? 1 : 0);
            i++;
        }
    }
    return (0);
}