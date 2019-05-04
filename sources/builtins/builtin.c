/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/23 13:13:48 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 14:06:58 by dewalter    ###    #+. /#+    ###.fr     */
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

void	builtin_set_check_duplicate(t_shell *shell, char *envl_var)
{
	int		n;
	char	*var_envl;
	char	*var_envp;
	BOOL	var_is_in_envp;

	var_is_in_envp = 0;
	var_envl = get_var(envl_var);
	n = 0;
	while (shell->envp[n])
	{
		var_envp = get_var(shell->envp[n]);
		if (ft_strcmp(var_envl, var_envp) == 0)
		{
			var_is_in_envp = 1;
			ft_strdel(&var_envp);
			break ;
		}
		ft_strdel(&var_envp);
		n++;
	}
	ft_strdel(&var_envl);
	if (var_is_in_envp == 0)
		ft_dprintf(1, "%s\n", envl_var);
}

int		builtin_set(t_shell *shell, char **args)
{
	int		i;

	if (args[1] == NULL)
	{
		i = 0;
		while (shell->envp && shell->envp[i])
			ft_dprintf(1, "%s\n", shell->envp[i++]);
		i = 0;
		while (shell->envl && shell->envl[i])
			builtin_set_check_duplicate(shell, shell->envl[i++]);
	}
	return (EXIT_SUCCESS);
}

BOOL	shell_is_builtin(t_cmd *elem, t_shell *shell)
{
	int i;

	if (elem->args[0] && builtin_localvar(&elem->args, elem->args_raw))
	{
		i = 0;
		while (elem->args[i])
			builtin_env_add(&shell->envp, &shell->envl, elem->args[i++]);
		ft_arrdel(&elem->args);
		return (1);
	}
	else if (elem->args[0] && (ft_strcmp("hash", elem->args[0]) == 0 ||
	!ft_strcmp("echo", elem->args[0]) || !ft_strcmp("cd", elem->args[0]) ||
	!ft_strcmp("set", elem->args[0]) || !ft_strcmp("unset", elem->args[0]) ||
	!ft_strcmp("export", elem->args[0]) || !ft_strcmp("type", elem->args[0]) ||
	!ft_strcmp("alias", elem->args[0]) || !ft_strcmp("fc", elem->args[0]) ||
	!ft_strcmp("unalias", elem->args[0]) || !ft_strcmp("test", elem->args[0]) ||
	!ft_strcmp("fg", elem->args[0]) || !ft_strcmp("bg", elem->args[0]) ||
	!ft_strcmp("jobs", elem->args[0]) ||
	!ft_strcmp("exit", elem->args[0])) && (elem->done = 1))
		return (1);
	else
		return (0);
}

void	shell_builtin2(t_cmd *elem, t_shell *shell)
{
	if (elem->args && elem->args[0] && ft_strcmp("type", elem->args[0]) == 0)
		elem->ret = builtin_type(elem->args + 1, shell->envp);
	if (elem->args && elem->args[0] && ft_strcmp("fc", elem->args[0]) == 0)
		elem->ret = builtin_fc(elem->args + 1, shell);
	if (elem->args && elem->args[0] && ft_strcmp("test", elem->args[0]) == 0)
		elem->ret = ft_builtin_test(elem->args, elem->args_raw);
	if (elem->args && elem->args[0] && ft_strcmp("fg", elem->args[0]) == 0)
		elem->ret = ft_builtin_fg(elem->args);
	if (elem->args && elem->args[0] && ft_strcmp("bg", elem->args[0]) == 0)
		elem->ret = ft_builtin_bg(elem->args);
	if (elem->args && elem->args[0] && ft_strcmp("jobs", elem->args[0]) == 0)
		elem->ret = ft_builtin_jobs(elem->args);
}

/*
** Return :
**   0 --> not builtin
**   1 --> is builtin
**  -1 --> need exit
** elem->ret contient 0 si builtin failed ou 1+ si succeeded ou -2 si exit fail
*/

int		shell_builtin(t_cmd *elem, t_shell *shell)
{
	int ret;

	ret = shell_is_builtin(elem, shell);
	if (elem->args && elem->args[0] && ft_strcmp("hash", elem->args[0]) == 0)
		elem->ret = ft_builtin_hash(elem->args, shell);
	if (elem->args && elem->args[0] && ft_strcmp("echo", elem->args[0]) == 0)
		elem->ret = builtin_echo(elem->args, elem->output);
	if (elem->args && elem->args[0] && ft_strcmp("cd", elem->args[0]) == 0)
		elem->ret = builtin_cd(elem->args, &shell->envp);
	if (elem->args && elem->args[0] && ft_strcmp("set", elem->args[0]) == 0)
		elem->ret = builtin_set(shell, elem->args);
	if (elem->args && elem->args[0] && ft_strcmp("unset", elem->args[0]) == 0)
		elem->ret = check_builtin_unset(shell, elem->args);
	if (elem->args && elem->args[0] && ft_strcmp("export", elem->args[0]) == 0)
		elem->ret = check_builtin_export(shell, elem->args);
	if (elem->args && elem->args[0] && ft_strcmp("alias", elem->args[0]) == 0)
		elem->ret = builtin_alias(&shell->alias, elem->args + 1);
	if (elem->args && elem->args[0] && ft_strcmp("unalias", elem->args[0]) == 0)
		elem->ret = builtin_unalias(&shell->alias, elem->args + 1);
	shell_builtin2(elem, shell);
	if (elem->args && elem->args[0] && ft_strcmp("exit", elem->args[0]) == 0)
		return (builtin_exit(elem, shell));
	dprintf(2, "ret_builtin: %d\n", elem->ret);
	return (ret);
}
