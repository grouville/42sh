//
// Created by Yohan Thollet on 2019-04-15.
//

#ifndef INC_42H_SHELL_H
# define INC_42H_SHELL_H

# include <sys/types.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>
# include <pwd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
#include <strings.h>




/* A process is a single process.  */
typedef struct process
{
	struct process *next;       /* next process in pipeline */
	char **argv;                /* for exec */
	pid_t pid;                  /* process ID */
	char completed;             /* true if process has completed */
	char stopped;               /* true if process has stopped */
	int status;                 /* reported status value */
}				t_process;


/* A job is a pipeline of processes.  */
typedef struct job
{
	struct job *next;           /* next active job */
	char *command;              /* command line, used for messages */
	t_process *first_process;     /* list of processes in this job */
	pid_t pgid;                 /* process group ID */
	char notified;              /* true if user told about stopped job */
	struct termios tmodes;      /* saved terminal modes */
	int stdin, stdout, stderr;  /* standard i/o channels */
}				t_job;

/* The active jobs are linked into a list.  This is its head.   */
t_job *first_job;
pid_t shell_pgid;
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;


void launch_process (t_process *p, pid_t pgid,
					 int infile, int outfile, int errfile,
					 int foreground);
void	launch_job (t_job *j, int foreground);
void	put_job_in_background (t_job *j, int cont);
void	put_job_in_foreground (t_job *j, int cont);
int		mark_process_status (pid_t pid, int status);
void 	update_status (void);
void	wait_for_job (t_job *j);
void format_job_info (t_job *j, const char *status);
void do_job_notification (void);
void mark_job_as_running (t_job *j);
void continue_job (t_job *j, int foreground);


//Here are some utility functions that are used for operating on job objects.

/* Find the active job with the indicated pgid.  */
t_job *find_job (pid_t pgid);


/* Return true if all processes in the job have stopped or completed.  */
int job_is_stopped (t_job *j);


/* Return true if all processes in the job have completed.  */
int job_is_completed (t_job *j);


#endif //INC_42H_SHELL_H
