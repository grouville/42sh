/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_process_sig.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/04 22:07:38 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 22:07:57 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	ft_putendl_fd(char const *s, int fd)
{
	if (s != NULL)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}

int		manage_sig_term_ret2(int ret)
{
	if (ret == 11)
		ft_putendl_fd("Segmentation fault: 11", 2);
	else if (ret == 13)
		ft_putendl_fd("Broken pipe: 13", 2);
	else if (ret == 16)
		ft_putendl_fd("Stack fault: 16", 2);
	return (128 + ret);
}

int			manage_sig_term_ret1(int ret)
{
	if (ret == 6)
		ft_putendl_fd("Abort trap: 6", 2);
	else if (ret == 7 || ret == 0)
		ft_putendl_fd("Bus error: 10", 2);
	else if (ret == 8)
		ft_putendl_fd("Floating-point exception: 8", 2);
	else if (ret == 4735)
		return (4735);
	else
		return (manage_sig_term_ret2(ret));
	return (ret + 128);
}
