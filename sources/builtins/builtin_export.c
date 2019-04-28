/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_export.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/11 17:33:02 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 17:33:02 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	builtin_export_envl_to_envp(t_shell *shell, char *cmd)
{
	int		i;
	char 	*var;
	char 	*value;

	i = 0;
	while (shell->envl[i])
	{
		var = get_var(shell->envl[i]);
		if (ft_strcmp(var, cmd) == 0)
		{
			value = get_value(shell->envl[i]);
			shell->envp = append_key_env(shell->envp, var, value);
			ft_strdel(&value);
		}
		ft_strdel(&var);
		i++;
	}
}

void	builtin_export_add_var_envp(t_shell *shell, char *cmd)
{
	char	*var;
	char	*value;

	var = get_var(cmd);
	value = get_value(cmd);
	if (ft_strlen(var))
		if (!(check_replace_env_variable(&shell->envl, var, value)))
			shell->envl = append_key_env(shell->envl, var, value);
	if (ft_strlen(var))
		if (!(check_replace_env_variable(&shell->envp, var, value)))
			shell->envp = append_key_env(shell->envp, var, value);
	if (ft_strcmp("PATH", var) == 0 && shell->t)
		delete_hash_table(&(shell->t));
	ft_strdel(&var);
	ft_strdel(&value);
}

int		check_builtin_export(t_shell *shell, char **cmd)
{
	int		i;

	i = 0;
	if (cmd[1] == NULL)
		while (shell->envp[i] != NULL)
			ft_dprintf(1, "declare -x %s\n", shell->envp[i++]);
	else if (cmd[1] != NULL)
	{
		i = 1;
		while (cmd[i])
		{
			if (!ft_strchr(cmd[i], '='))
				builtin_export_envl_to_envp(shell, cmd[i]);
			else
				builtin_export_add_var_envp(shell, cmd[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
