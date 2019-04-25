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
*** - Aim of the function
*** - Check if usage is correct
*/

int             check_usage(char *cmd)
{
    int i;

    i = 0;
    if (cmd[0] == '-')
    {
        ft_dprintf(2, "fg: usage: fg [job_spec]\n");
        return (1);
    }
    return (0);
}

/*
*** - Aim of the function
*** - Check if arg is a number
*/

int             is_number(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (!ft_isdigit(cmd[i]))
            return (1);
        i++;
    }
    return (0);
}

/*
*** - Aim of the function :
*** - Retrieve the corresponding job, or print error if doesn't exist
*/

int         job_percentage_number_exists_or_not(char *cmd, int nb,
                t_job **job)
{
    t_job   *j;
    int		nb_bgjob;

    nb_bgjob = 1;
    j = getter_job()->first_job;
    while (j)
    {
        if (nb_bgjob == nb && j->sep == SPL_SPRLU && j->state == -1)
            break ;
        if (j->sep == SPL_SPRLU && j->state == -1)
			nb_bgjob += 1;
        j = j->next;
    }
    if (j && nb != 0)
        *job = j;
    else
    {
        ft_dprintf(2, nb == 0 ? "bash: fg: current: no such job\n"
            : "bash: fg: %s: no such job\n", cmd);
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

int             check_if_job_exists(char *cmd, t_job **j)
{
    if (!is_number(cmd))
        return (job_percentage_number_exists_or_not(cmd,
            ft_atoi(cmd), j));
    else if (*cmd == '%' && !is_number(cmd + 1))
        return (job_percentage_number_exists_or_not(cmd,
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
*** - Retrieve the number of the last job put in bg
*/

int         find_last_job_put_in_background(void)
{
    t_job   *j;
    t_js    *jsig;
    int		nb_bgjob;

    nb_bgjob = 0;
    jsig = getter_job();
    j = jsig->first_job;
    while (j)
    {
        if (j->sep == SPL_SPRLU && j->state == -1)
			nb_bgjob += 1;
        j = j->next;
    }
    return (nb_bgjob);
}

/*
*** - Aim of the function :
*** - Manage the fg builtin
*/

int			    ft_builtin_fg(char **cmd)
{
    t_job   *j;
    int     job_number;

    if (ft_arrlen(cmd) == 1)
    {
        job_number = find_last_job_put_in_background();
        if (job_percentage_number_exists_or_not(*cmd,
            job_number, &j))
            return (1);
    }
    else
    {
        if (check_usage(cmd[1]))
            return (2);
        if (check_if_job_exists(cmd[1], &j))
            return (1);
    }
    put_job_in_foreground(j, job_is_stopped(j) ? 1 : 0);
    return (0);
}