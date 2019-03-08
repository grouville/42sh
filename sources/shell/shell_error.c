/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 17:55:32 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 17:55:32 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Include/shell.h"

int		shell_error_prepare(char *msg, char *elem)
{
	if (ft_strcmp(msg, "Is directory") == 0)
		ft_dprintf(2, "42sh: %s: : Is a directory\n", elem);
	else if (ft_strcmp(msg, "denied") == 0 || !ft_strcmp(msg, "pathdenied"))
		ft_dprintf(2, "42sh: %s: Permission denied\n", elem);
	else if (ft_strcmp(msg, "not found") == 0)
		ft_dprintf(2, "42sh: %s: No such file or directory\n", elem);
	else if (ft_strcmp(msg, "bad fd") == 0)
		ft_dprintf(2, "42sh: %s: Bad file descriptor\n", elem + 1);
	else if (ft_strcmp(msg, "ambiguous") == 0)
		ft_dprintf(2, "42sh: %s: ambiguous redirect\n", elem + 1);
	return (0);
}

int		shell_error_env(char *msg)
{
	if (ft_strcmp(msg, "env set usage") == 0)
		ft_dprintf(2, "42sh: setenv: invalid argument\n"
						"usage: setenv VAR VALUE\n");
	else if (ft_strcmp(msg, "env unset usage") == 0)
		ft_dprintf(2, "42sh: unsetenv: invalid argument\n"
						"usage: unsetenv VAR\n");
	else if (ft_strcmp(msg, "env usage") == 0)
		ft_dprintf(2, "42sh: env: invalid argument\nusage: env VAR\n");
	else if (ft_strcmp(msg, "env $HOME not set") == 0)
		ft_dprintf(2, "42sh: $HOME env not set\n");
	else
		ft_dprintf(2, "Error ENV : unknown msg type <%s>\n", msg);
	return (0);
}

/*
** Print un message d'erreur ou/et exit le plus proprement possible.
** {type} commence par un code suivant :
**      - env : erreur lié aux variable environement
**		- mlc : erreur de malloc. Récupère les {n} var à free avec ap puis exit
**		- gnl : fail GNL ou reception signal Ctrl-D
**
** Necessite de supprimer l'error de malloc lors malloc(32000000000000000+)
*/

int		shell_error(char *type, int n, ...)
{
	va_list	ap;

	va_start(ap, n);
	if (type[0] == 'e' && type[1] == 'n' && type[2] == 'v')
		return (shell_error_env(type));
	else if (type[0] == 'g' && type[1] == 'n' && type[2] == 'l')
	{
		va_end(ap);
		write(1, " exit\n", 6);
		exit(EXIT_FAILURE);
	}
	else if (type[0] == 'm' && type[1] == 'l' && type[2] == 'c')
	{
		ft_dprintf(2, "Fatal: failed to allocate %zu bytes\n",
				va_arg(ap, size_t));
		va_end(ap);
		exit(EXIT_FAILURE);
	}
	va_end(ap);
	return (0);
}

void	*shl_mlc(char *type, int n, ...)
{
	va_list	ap;
	void	*ret;

	va_start(ap, n);
	if (type[0] == 'c' && type[1] == 'm' && type[2] == 'd' &&
			!(ret = (void *)ft_memalloc(sizeof(t_cmd))))
		shell_error("mlc", 3, va_arg(ap, char **), va_arg(ap, char **),
					va_arg(ap, size_t));
	if (type[0] == 'a' && type[1] == 'r' && type[2] == 'g' &&
		!(ret = (void *)ft_memalloc(sizeof(t_cmd))))
		shell_error("mlc", 3, va_arg(ap, char **), va_arg(ap, char **),
					va_arg(ap, size_t));
	if (type[0] == 'a' && type[1] == 'r' && type[2] == 'g' && type[3] == 's' &&
			!(ret = (void *)ft_memalloc(va_arg(ap, size_t))))
		shell_error("mlc", 3, va_arg(ap, char **), va_arg(ap, char **),
					va_arg(ap, size_t));
	va_end(ap);
	return (ret);
}
