/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/05 16:27:06 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 16:27:08 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define BUFF_READ 1000

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>
# include <pwd.h>
# include "editor.h"
# include "libft.h"
# include "hash_table.h"
# include "test.h"

typedef struct		s_process
{
	char			*fd_stdin;
	char			*stdin_send;
	char			*fd_stdout;
	int				fd_fileout;
	char			*fd_stderr;
	int				fd_fileerr;
	int				last_redi;
}					t_process;

typedef struct		s_stdout
{
	BOOL			append;
	int				from;
	char			*to;
	struct s_stdout	*next;
	struct s_stdout	*start;
}					t_output;

/*
** Le premier maillon de t_cmd est vide et est pointé par tous les autres
** {hrdc[i] et std_in[i]} peuvent valoir soit une string, soit -1 si non rempli
** soit -2 si la chaine de char se trouve dans le prochain arg.
** Dans shell_hrdc, {hrdc[i]} prendra la valeur de -3 pour être indiqué
** comme rempli par l'utilisateur.
** hrdc_stdin peut avoir comme valeur -1 lors du parsing pour attendre d'être
** rempli
*/

typedef struct		s_cmd
{
	char			*exec;
	char			**args;
	char			**args_raw;
	t_output		*output;
	char			**input;
	char			**hrdc;
	t_process		process;
	int				sep;
	int				ret;
	pid_t			pid;
	BOOL			done;
	BOOL			stopped;
	BOOL			signal;
	int				status;
	BOOL			bad_substitution;
	char			**envl_exec;
	struct s_cmd	*next_cmd;
	struct s_cmd	*start;
}					t_cmd;

typedef struct		s_job
{
	t_cmd			*cmds;
	int				sep;
	int				num;
	pid_t			pgid;
	int				state;
	int				running;
	char			notified;
	char			notified_crtrz;
	struct termios	tmodes;
	struct s_job	*next;
}					t_job;

typedef struct		s_job_signal
{
	t_job			*first_job;
	pid_t			shell_pgid;
	struct termios	shell_tmodes;
	int				shell_terminal;
	int				shell_is_interactive;
}					t_js;

typedef struct		s_type
{
	int		i;
	int		j;
	int		match[2];
	char	*op;
	char	*b_path;
	char	**bin;
}					t_type;

typedef struct		s_shell
{
	char			**envp;
	char			**envl;
	char			**alias;
	char			*str;
	char			*hrdc_tmp;
	char			*hist_path;
	int				ret;
	t_data			*hist;
	t_htable		*t;
	int				count;
	int				is_interactive;
}					t_shell;

typedef	struct		s_fc
{
	int				i;
	int				fd;
	int				nb;
	char			*editor;
	char			*first;
	char			*last;
	int				ret;
	int				heredoc[2];
	char			*op;
	t_shell			*shl;
	t_cmd			*cmd;
	t_data			*cmd_list;
}					t_fc;

typedef struct		s_norme
{
	t_shell			*shl;
	t_prompt		prmt;
	t_cmd			*cmd;
	t_shortcut		ret;
	t_job			*jobs;
}					t_norme;

typedef struct		s_alias
{
	BOOL			aliased;
	char 			quote;
	int 			i;
	int 			len;
	char 			*tmp;
	char 			*tmp2;
	char 			*alias;
	char 			*last_alias;
}					t_alias;

typedef enum		e_sep
{
	SPL_PIPE = 1,
	PTN_VRGL = 2,
	DBL_PIPE = 3,
	DBL_SPRLU = 4,
	SPL_SPRLU = 5,
}					t_sep;

typedef enum		e_error
{
	SPL_QUOTE,
	DBL_QUOTE,
	DBL_SEP_OR_BK,
}					t_error;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  Builtin                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int					builtin_cd(char **cmd, char ***envp);
char				*cd_rmv_last_path(char *cur_dir);
void				builtin_setenv(char ***envp, char *key, char *value);
char				**rmv_key_env(char **envp, char *key);
void				builtin_export_print(char **envp, char *key);
int					builtin_echo(char **cmd, t_output *output);
int					builtin_env_add(char ***envp, char ***envl, char *arg);
int					builtin_exit(t_cmd *elem, t_shell *shell);
char				*get_value(char *arg);

int					builtin_type(char **args, char **envp, char **envl);
int					builtin_get_options(char **options, char **args,
					char *possibility, int num);
int					builtin_type_check_builtin(char *d_name);
void				builtin_type_display(char *d_name, char *bin,
											char *options, int mode);
int					builtin_alias(char ***alias, char **args);
char				**builtin_alias_get_alias_from_file(char *file);
void				shell_check_alias(t_shell *shell, t_cmd *next, int index);
int					check_executable_file(char *path);
int					builtin_unalias(char ***alias, char **args);

int					shell_builtin(t_cmd *elem, t_shell *shell);
char				*get_envp(char **envp, char *var);
char				*get_var(char *var_key);
char				**append_key_env(char **envp, char *key, char *value);
int					check_replace_env_variable(char ***env, char *var,
													char *value);
int					check_builtin_export(t_shell *shell, char **cmd);
int					builtin_fc(char **args, t_shell *shell);
int					builtin_fc_search_occurence(t_fc *fc, t_data *hist);
void				builtin_fc_execute_commands(t_fc *fc, t_shell *shell);
void				builtin_fc_search_first_and_last(char **args, t_fc *fc);
int					shell_command_execution(t_shell *shl, t_cmd **cmd,
						t_shortcut ret, t_prompt *prmt);
BOOL				is_var(char *arg);
int					builtin_localvar(t_cmd *elem);
int					ft_builtin_fg(char **cmd);
int					ft_builtin_bg(char **cmd);
int					find_last_job_put_in_background(void);
int					check_if_job_exists(char *cmd, t_job **j);
int					job_percentage_number_exists_or_not_fg(char *cmd, int nb,
															t_job **job);
int					check_usage(char *cmd);
int					is_number(char *cmd);
BOOL				shell_is_builtin(t_cmd *elem);
BOOL				shell_is_builtin_str(char *str);
int					ft_builtin_jobs(char **cmd);
void				free_job_after_signal(t_job **job);
int					ft_usage_error(char *cmd, int ret);
int					ft_len_array_char(char **av);
t_job				*find_jobnum(char *num, t_job **j);
void				process_jobs_option_l(t_job **job);
t_job				*find_jobnum(char *num, t_job **j);
int					ft_normalize_av(char ***av, char *c, int *begin,
						BOOL *other_arg);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               split_shell                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_cmd				*shell_split(char *line, char **envp, t_prompt *prompt);
t_cmd				*get_args(char **line, char **envp, t_prompt *prompt);
int					shell_envpsub(char **arg, char **envp, char **envl);
int					shell_argsub_env(char **arg, int i, char **envp,
										char **envl);
int					shell_process(t_job *jobs, t_cmd **cmd, t_shell *shell);
t_output			*shell_std_out(char **arg, t_output **first_redi,
										char quote);
void				shell_std_in(char **arg, char quote, t_cmd *cmd);

BOOL				cmd_check(t_cmd **cmd, t_shell *shell, t_prompt *prompt);
int					hrdc_fill(t_prompt *prompt, t_cmd **cmd, t_shell *shell,
						t_shortcut ret);
void				complete_all_stdin(char **arg, char quote, t_cmd *cmd);
size_t				len_arg(char *str, char quote);
void				clean_cmd(t_cmd **cmd);
char				*shell_trim(char **str);
int					check_last_quote(char *arg, char quote);
BOOL				stdout_to(t_output *redis);
int					len_stdout_to(char *str);
t_output			*get_last_stdout(t_output *redi);
char				*complete_stdout_to(char **arg, t_output *add_to);
int					shell_stdin_sub(char **arg, int i, char ***std_in);
char				**add_stdin(char **hrdc);
int					shell_clean_data(t_cmd **cmd, t_shell *shell,
										BOOL hrdc_tmp);
int					len_stdin(char *str, char quote);
char				*get_stdout_to(char *redi, int pos);
void				read_lexing(t_cmd *elem);
BOOL				triple_chevrons(char *str);
BOOL				iscomplet(char *str, t_prompt *prompt);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 Process                                    ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void				shell_prepare(t_job *jobs, t_cmd *cmd);
char				*shell_getpathexec(char *exec, char **all_env);
void				shell_clean_emptyargs(t_cmd *link);
int					complete_stdout_path(t_output *std_out, t_shell *shell);
int					shell_error_prepare(char *msg, char *elem);
int					shell_read_input(t_cmd *elem, t_shell *shell);
int					shell_set_output(t_cmd *elem, t_shell *shell);
void				shell_set_output_file(t_output *output, t_cmd *elem,
						int fd_file);
int					shell_exec(t_cmd *elem, t_shell *shell, t_job *job);
void				shell_prepare_args(t_cmd *elem, t_shell *shell);
void				shell_save_fd(int fd[3]);
void				shell_reinit_fd(int *fd);
void				shell_prcs_sigint(int signum);
int					ft_read_file(char *filename, char **file_content);
int					path_to_output_exist(char *output);
int					complete_output_paths(char **output_to, t_shell *shell);
int					path_to_output_recheable(char *output);
void				shell_plomberie(t_process process);
int					get_stdin(t_shell *shell, t_prompt *prompt);
int					shell_exec_pipes(t_cmd **elem, t_shell *shell, t_job *job);
void				shell_set_fd_null(t_output *output, t_cmd *elem);
int					get_nbarg(char *str, t_prompt *prompt);
char				*get_arg(char **str, t_cmd *cmd);
void				shell_ret(t_cmd *elem, t_shell *shell);
t_cmd				*shell_process_skip_cmd(t_cmd *elem, t_sep sep);
int					manage_sig_term_ret(int ret);
void				ft_putendl_fd(char const *s, int fd);
void				shell_prepare_jobs(t_job *first_jobs, t_cmd *cmd);
void				child_signals_to_dfl(void);
int					shell_exec_error(t_cmd *elem);
void				shell_exec_print_error(t_cmd *elem);
void				shell_prepare_jobs_boucle(t_cmd *elem, t_job *first_jobs,
						t_job *job);
BOOL				shell_add_local_var(t_cmd *elem, t_shell *shell);
void				shell_add_envl_exec(char **envl_to_add, t_shell *shell);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  Tools                                     ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int					check_if_env_var_existing(char **env, char*var);
char				**init_env(char **envp);
int					shell_error(char *type, int n, ...);
int					shell_error_env(char *msg);
void				clean_shell(t_shell **shell);
int					ft_isfile(char *file_path);
int					ft_isdir(char *path);
char				*get_cur_dir(void);
void				shl_quotesub(char *arg);
void				*shl_mlc(char *type, int n, ...);
int					shell_exit(t_shell **shell);
void				shell_init(t_shell **shell, t_prompt *prompt, t_cmd **cmd,
						t_job **job);
char				*get_next_hrdc(char **hrdc);
BOOL				check_expansions(t_shell *shell);
char				*ft_strcutword(char **str, int i, int len_word);
BOOL				check_syntax_err(t_cmd *cmd);
size_t				shell_argsub_len_var(char *argi);
char				*ft_remplace_char_by_str(char *word, char c, char *str);
int					check_synthax_stdout_to(t_output *redis);
void				clean_arr_mlti(char **arr);
void				clean_redi(t_output **redi);
void				check_hash_then_path(t_cmd *elem, t_shell *shell);
char				**ft_arrjoin(char **arr1, char **arr2);
char				*shell_alias(char *str, char **shl_al);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  Hash                                      ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

/*
** - delete_print_search.c
*/

void				ft_print_hash(t_shell *env);
int					ft_builtin_hash(char **cmd, t_shell *env);
int					ft_usage_is_good(char *limitor, char *str);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  Jobs                                      ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

/*
** - shell_init_jobs.c
*/

void				put_job_in_background(t_job *j, int cont);
void				put_job_in_foreground(t_job *j, int cont);
int					mark_process_status (pid_t pid, int status);
void				update_status(void);
void				wait_for_job(t_job *j);
void				do_job_notification(t_cmd **cmd, t_shell *shl,
										t_cmd **cmd_jobs);
void				mark_job_as_running(t_job *j);
void				continue_job(t_job *j, int foreground);
void				format_job_info_signal(t_job *j, const char *status,
						int nb_bgjob);
void				format_job_info(t_job *j, const char *status,
						int nb_bgjob);
t_job				*find_job(pid_t pgid);
int					job_is_stopped(t_job *j);
void				print_sep(int fd, t_sep sep);
int					job_is_completed(t_job *j);
void				process_init_shell_for_job(void);
void				free_job(t_job **j, t_cmd **cmd);
t_js				*getter_job(void);
void				put_process_suspended(t_job *j, t_cmd *elem);
int					check_jobs_on_exit(t_shell *shl);
int					job_is_signaled(t_job *j);
void				clean_jobs_all(void);
int					check_last_command_jobs(t_cmd **cmd);
int					check_last_command_fc(void);
int					clean_jobs(t_job **jobs);

#endif
