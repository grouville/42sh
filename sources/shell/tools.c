/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/05 23:19:43 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/04 18:32:42 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

int			init_terminal_data(void)
{
	static char	term_buffer[2048];
	char		*termtype;
	int			success;

	if (!isatty(0))
	{
		ft_putstr("File descriptor does not refer to a terminal device.\n");
		return (1);
	}
	if (!(termtype = getenv("TERM")))
		termtype = "xterm-256color";
	success = tgetent(term_buffer, termtype);
	if (success < 0)
	{
		ft_putstr("Could not access the termcap data base.\n");
		return (1);
	}
	if (success == 0)
	{
		ft_putstr("Terminal type `");
		ft_putstr(termtype);
		ft_putendl("' is not defined.");
		return (1);
	}
	return (0);
}

t_shell		*init_shell(char **envp)
{
	t_shell			*shell;

	if (!(shell = malloc(sizeof(t_shell))))
		exit(EXIT_FAILURE);
	ft_bzero(shell, sizeof(t_shell));
	if (!(shell->envp = init_env(ft_arrdup(envp))))
	{
		free(shell);
		exit(EXIT_FAILURE);
	}
	if (check_if_env_var_existing(shell->envp, "OLDPWD"))
		shell->envp = rmv_key_env(shell->envp, "OLDPWD");
	shell->hist_path =
			build_full_path(get_envp(shell->envp, "HOME"), ".42sh_history");
	shell->hist = init_hist(shell->hist_path);
	shell->alias = builtin_alias_get_alias_from_file(".42sh_alias");
	shell->envl = (char **)malloc(sizeof(char *));
	shell->envl[0] = NULL;
	shell->envl = append_key_env(shell->envl, "?", "0");
	shell->count = -1;
	if (!shell->hist)
		exit(EXIT_FAILURE);
	return (shell);
}

void		shell_init(t_shell **shell, t_prompt *prompt,
					   t_cmd **cmd, char **env, t_job **jobs)
{
	t_js	*jsig;

	jsig = getter_job();
	if (init_terminal_data())
		exit(EXIT_FAILURE);
	*shell = init_shell(env);
	*prompt = PROMPT;
	*cmd = NULL;
	*jobs = malloc(sizeof(t_job));
	ft_bzero(*jobs, sizeof(t_job));
	jsig->first_job = *jobs;
	process_init_shell_for_job();
}

int			shell_exit(t_shell **shell)
{
	int		ret;

	if ((*shell)->t)
		delete_hash_table(&((*shell)->t));
	if ((*shell)->hist)
		fill_hist_file((*shell)->hist, (*shell)->hist_path);
	ft_strdel(&(*shell)->hist_path);
	if ((*shell)->alias)
		ft_arrdel(&(*shell)->alias);
	ret = (*shell)->ret;
	clean_shell(shell);
	clean_jobs_all();
	return (ret);
}

/*
** Retourne le path absolu.
** On commence avec 8 octet puis on monte puissance 2
*/

char		*get_cur_dir(void)
{
	size_t	buf;
	char	*dir;

	buf = 8;
	dir = ft_strnew(buf);
	while (getcwd(dir, buf) == NULL)
	{
		free(dir);
		buf *= 2;
		dir = ft_strnew(buf);
	}
	return (dir);
}
