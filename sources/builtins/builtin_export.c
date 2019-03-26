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

void	builtin_export_add_var(t_shell *shell, char **cmd)
{
	int		i;
	char	*var;
	char	*value;

	i = 1;
	while (cmd[i])
	{
		var = get_var(cmd[i]);
		value = get_value(cmd[i]);
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
		i++;
	}
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
			if (!ft_strchr(cmd[i++], '='))
				return (shell_error_env("export usage"));
		builtin_export_add_var(shell, cmd);
	}
	return (EXIT_SUCCESS);
}
