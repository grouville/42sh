/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/23 13:13:48 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 04:59:23 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int		check_builtin_unset(t_shell *shell, char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		shell_envpsub(&args[i], shell->envp, shell->envl);
		shl_quotesub(args[i]);
		if (get_envp(shell->envp, args[i]))
			shell->envp = rmv_key_env(shell->envp, args[i]);
		if (get_envp(shell->envl, args[i]))
			shell->envl = rmv_key_env(shell->envl, args[i]);
		if (ft_strcmp("PATH", args[i]) == 0 && shell->t)
			delete_hash_table(&(shell->t));
		i++;
	}
	return (0);
}

int		check_builtin_set(t_shell *shell, char **args)
{
	int i;

	i = 0;
	if (args[1] == NULL)
		while (shell->envl[i])
			ft_dprintf(1, "%s\n", shell->envl[i++]);
	return (EXIT_SUCCESS);
}

int		check_shell_variable(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
		if (arg[i++] == '=')
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
	if (elem->args[0] && ft_strcmp("hash", elem->args[0]) == 0)
		elem->ret = ft_builtin_hash(elem->args, shell);
	else if (elem->args[0] && ft_strcmp("echo", elem->args[0]) == 0)
		elem->ret = builtin_echo(elem->args);
	else if (elem->args[0] && ft_strcmp("cd", elem->args[0]) == 0)
		elem->ret = builtin_cd(elem->args, &shell->envp);
	else if (elem->args[0] && ft_strcmp("set", elem->args[0]) == 0)
		elem->ret = check_builtin_set(shell, elem->args);
	else if (elem->args[0] && ft_strcmp("unset", elem->args[0]) == 0)
		elem->ret = check_builtin_unset(shell, elem->args);
	else if (elem->args[0] && ft_strcmp("export", elem->args[0]) == 0)
		elem->ret = check_builtin_export(shell, elem->args);
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
