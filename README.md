# 42sh

This school project is a homemade shell. 
We decide to choose __bash 5.0__ as shell reference.

----------------

It has the following implementations :
* Run commands with their parameters and PATH monitoring
* Error monitoring, without using erno, and return values of commands
* Full edition of commands line
* Redirection and aggregation operators :
  * `>`
  * `>>`
  * `<`
  * `<<`
  * `<<<`
  * `>&`
  * `<&`
* pipe `|`
* separators `;`
* built-ins :
  * `cd`
  * `echo`
  * `exit`
  * `type`
* The following logical operators `&&` and `||`
* Monitoring of intern shell variables
  * Intern variable creation depending on syntax:`name=value`
  * Intern variable exportation to the environment, via built-in `export`
  * Possibility to list shell intern variables via built-in `set`
  * Intern and environement variables revocation, via built-in `unset`
  * Environment variable creation for unique command, for instance: `HOME=/tmp cd`
  * Simple expansion of parameters depending on syntax `${}`
* Job control monitoring, with buitl-ins `jobs`, `fg`, `bg` and the `&` operator
* A correct monitoring of all signals
* Each built-in must have the enounced options by POSIX standard, except for explicit case as `set` or `unset`
* Inhibitors `”`(double quote), `’`(simple quote) and `\`(backslash)
* Contextual dynamic completion of commands, built-ins, files, internal and environment variables
* Alias management via built-ins `alias` and `unalias`
* A hash table and built-in `hash` to interact with it
* The built-in `test` with the following operators: -b,-c,-d,-e,-f,-g,-L,-p,-r,-S,-s,-u,-w,-x,-z,=,!=,-eq,-ne,-ge,-lt,-le,!. As well as the possibility of a simple operand, without operator.

----------------

Only the following functions has been used :

`_access`
`_chdir`
`_close`
`_closedir`
`_dup`
`_dup2`
`_environ`
`_execve`
`_exit`
`_fork`
`_free`
`_getcwd`
`_getenv`
`_getpgrp`
`_getpid`
`_getpwnam`
`_getpwuid`
`_getuid`
`_ioctl`
`_isatty`
`_kill`
`_lstat`
`_malloc`
`_memcpy`
`_nanosleep`
`_open`
`_opendir`
`_pipe`
`_read`
`_readdir`
`_setpgid`
`_signal`
`_stat`
`_tcgetattr`
`_tcgetpgrp`
`_tcsetattr`
`_tcsetpgrp`
`_tgetent`
`_tgetstr`
`_tgoto`
`_tputs`
`_uname`
`_unlink`
`_waitpid`
`_write`

