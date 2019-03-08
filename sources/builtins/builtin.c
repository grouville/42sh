/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/23 13:13:48 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 15:22:12 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Include/shell.h"

int		check_builtin_setenv(char ***envp, char **cmd)
{
	if (cmd[1] != NULL && cmd[2] != NULL && cmd[3] == NULL)
		builtin_setenv(envp, cmd[1], cmd[2]);
	else
		return (shell_error_env("env set usage"));
	return (1);
}

int		check_builtin_unsetenv(char ***envp, char **cmd)
{
	if (cmd[1] != NULL && cmd[2] == NULL && get_envp(*envp, cmd[1]))
		*envp = rmv_key_env(*envp, cmd[1]);
	else
		return (shell_error_env("env unset usage"));
	return (1);
}

int		check_builtin_env(char ***envp, char **cmd)
{
	if (cmd[1] == NULL)
		builtin_env(*envp, NULL);
	else if (cmd[1] != NULL && cmd[2] == NULL)
		builtin_env(*envp, cmd[1]);
	else
		return (shell_error_env("env usage"));
	return (1);
}

int		check_shell_variable(char *arg)
{
	int i;

	i = -1;
	while (arg[++i])
		if (arg[i] == '=')
			return (1);
	return (0);
}

/*
** Return value :
**  - 0 not builtin
**  - 1 is builtin
**  - -1 need exit
** elem->ret contient 0 si builtin failed ou 1+ si succeeded ou -2 si exit fail
*/

int		shell_builtin(t_cmd *elem, t_shell *shell)
{
	if (elem->args[0] && ft_strcmp("echo", elem->args[0]) == 0)
		elem->ret = builtin_echo(elem->args);
	else if (elem->args[0] && ft_strcmp("cd", elem->args[0]) == 0)
		elem->ret = builtin_cd(elem->args, &shell->envp);
	else if (elem->args[0] && ft_strcmp("setenv", elem->args[0]) == 0)
		elem->ret = check_builtin_setenv(&shell->envp, elem->args);
	else if (elem->args[0] && ft_strcmp("unsetenv", elem->args[0]) == 0)
		elem->ret = check_builtin_unsetenv(&shell->envp, elem->args);
	else if (elem->args[0] && ft_strcmp("env", elem->args[0]) == 0)
		elem->ret = check_builtin_env(&shell->envp, elem->args);
	else if (elem->args[0] && check_shell_variable(elem->args[0]))
		elem->ret = builtin_env_all(&shell->envp, &shell->envl, elem->args);
	else if (elem->args[0] && ft_strcmp("type", elem->args[0]) == 0)
		elem->ret = builtin_type(elem->args + 1, shell->envp);
	else if (elem->args[0] && ft_strcmp("alias", elem->args[0]) == 0)
		elem->ret = builtin_alias(&shell->alias, elem->args + 1);
	else if (elem->args[0] && ft_strcmp("unalias", elem->args[0]) == 0)
		elem->ret = builtin_unalias(&shell->alias, elem->args + 1);
	else if (elem->args[0] && ft_strcmp("exit", elem->args[0]) == 0)
		return ((elem->ret = builtin_exit(elem->args)) == -2 ? 1 : -1);
	else
		return (0);
	return (1);
}
