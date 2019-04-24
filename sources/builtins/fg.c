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

int         job_percentage_number_exists_or_not(char *cmd, int nb,
                t_job **job)
{
    t_job   *j;
    int		nb_bgjob;

    nb_bgjob = 0;
    j = getter_job()->first_job;
    while (j)
    {
        if (nb_bgjob == nb)
            break ;
        if (j->sep == SPL_SPRLU && j->state == -1)
			nb_bgjob += 1;
        j = j->next;
    }
    if (j)
        *job = j;
    else
    {
        ft_dprintf(2, "bash: fg: *s: no such job\n", cmd);
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
    {
        *j = find_job(ft_atoi(cmd));
        if (!*j)
        {
            ft_dprintf(2, "bash: fg: %s: no such job\n", cmd);
            return (1);
        }
        else
            *j = find_job(ft_atoi(cmd));
    }
    else
    {
        if (*cmd == '%')
        {
            if (!is_number(cmd + 1))
            {
                printf("merde\n");
                return (job_percentage_number_exists_or_not(cmd,
                    ft_atoi(cmd + 1), j));
            }
            else
            {
                printf("ecnore plus\n");
                ft_dprintf(2, "bash: fg: %s: no such job\n", cmd);
                return (1);
            }   
        }
        else
        {
            printf("d'autant plus\n");
            ft_dprintf(2, "bash: fg: %s: no such job\n", cmd);
            return (1);
        }
    }
    return (0);
}

// No job == return 1
// Usage error == return 2

int			    ft_builtin_fg(char **cmd)
{
    t_job *j;

    if (check_usage(cmd[1]))
        return (2);
    if (check_if_job_exists(cmd[1], &j))
        return (1);
    // if job is stopped, continue, otherwise, let it
    put_job_in_foreground(j, job_is_stopped(j) ? 1 : 0);
    // dprintf(1, "%s\n", *cmd);
    return (0);
}