# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/05/04 20:51:29 by ythollet     #+#   ##    ##    #+#        #
#    Updated: 2019/05/05 17:06:40 by dewalter    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NOCOLOR=\033[0m
VERT=\033[32;05m
JAUNE=\033[33m
PURPLE=\033[0;35m
CFLAGS = -g #-Wall -Wextra -Werror

NAME = 42sh

DIR_LIB = ./Libft/
DIR_INC = ./include/
DIR_INC2 = -I ./include/ -I ./libft/Includes/
DIR_SRC = ./Sources/
DIR_OBJ = ./Objects/

SRCS =  shell/main.c \
        shell/tools.c \
        shell/ft_tools.c \
        shell/ft_tools2.c \
        shell/shell_tools.c \
        shell/shell_envsub.c \
        shell/shell_argsub_env.c \
        shell/shell_env_init.c \
        shell/shell_error.c \
        shell/shell_hrdc.c \
        shell/shell_check.c \
        shell/shell_alias.c \
        shell/shell_check_syntax.c \
        shell/shell_check_syntax_tools.c \
        shell/shell_clean.c \
        shell/shell_clean_tools.c \
		shell/shell_check_expansions.c \
        shell/split/shell_split.c \
        shell/split/shell_split_getargs.c \
 		shell/split/shell_split_tools.c \
 		shell/split/shell_split_stdout.c \
 		shell/split/shell_split_stdout_tools.c \
 		shell/split/shell_split_stdin.c \
 		shell/split/shell_split_stdin_tools.c \
        shell/process/shell_process.c \
        shell/process/shell_process_prepare.c \
        shell/process/shell_process_prepare_tools.c \
        shell/process/shell_process_output.c \
        shell/process/shell_process_output_tools.c \
        shell/process/shell_process_input.c \
        shell/process/shell_process_tools.c \
        shell/process/shell_process_getpathcmd.c \
        shell/process/shell_process_exec.c \
        shell/process/shell_process_plomberie.c \
        shell/process/shell_process_pipe.c \
        shell/process/shell_process_sig.c \
		shell/process/shell_process_norm.c \
        shell/jobs/shell_init_jobs.c \
		shell/jobs/check_jobs_on_exit.c \
        shell/jobs/wait_job.c \
        shell/jobs/job_is.c \
        shell/jobs/put_job.c \
		shell/jobs/job_tools.c \
		shell/jobs/do_job_notif.c \
        shell/jobs/stop_terminated_jobs.c \
		shell/jobs/getter_job.c \
		builtins/builtin_cd.c \
		builtins/builtin_cd_tools.c \
        builtins/builtin_allenv.c \
        builtins/builtin_echo.c \
        builtins/builtin_envl.c \
        builtins/builtin_type.c \
        builtins/builtin_type_tools.c \
        builtins/builtin_alias.c \
		builtins/builtin_alias_tools.c \
        builtins/builtin_unalias.c \
        builtins/builtin_exit.c \
        builtins/builtin_export.c \
        builtins/builtin.c \
		builtins/builtin_tools.c \
		builtins/builtin_fc.c \
		builtins/builtin_fc_search_occurence.c \
		builtins/builtin_fc_execute_command.c \
		builtins/builtin_localvar.c \
		builtins/builtin_jobs.c \
		builtins/builtin_jobs_l_option.c \
		builtins/utils_job.c \
		builtins/utils_builtin.c \
		builtins/fg.c \
		builtins/bg.c \
        editor/get_stdin.c \
		editor/prompt.c \
		editor/cursor_position.c \
		editor/backspace.c \
		editor/go_to_of_line.c \
		editor/move_cursor_left.c \
		editor/move_cursor_right.c \
		editor/move_cursor_up.c \
		editor/move_cursor_down.c \
		editor/move_word.c \
		editor/add_char.c \
		editor/paste_line.c \
		editor/term_init.c \
		editor/tools.c \
		editor/window_resize.c \
		editor/insert_del_line.c \
		editor/delete_from_cursor_to_end.c \
		editor/clear_window.c \
		editor/paste_clipboard.c \
		editor/tabulator/tabulator_check.c \
		editor/tabulator/tabulator_check_mode.c \
		editor/tabulator/tabulator_put_row.c \
		editor/tabulator/tabulator_recup_data.c \
		editor/tabulator/tabulator_recup_folder_files.c \
		editor/tabulator/term_tabulator.c \
		editor/tabulator/tabulator_put_new_cmd.c \
		editor/tabulator/tabulator_check_if_var.c \
		editor/tabulator/tabulator_tools.c \
		editor/history/term_hist_recup_cmd.c \
		editor/history/term_history.c \
		editor/history/term_history_incremental_search.c \
		editor/history/term_history_incremental_search_print.c \
		hash/hash.c \
		hash/delete_print_search.c \
		hash/hash_function.c \
		hash/insert_element_hash.c \
		hash/new_elements.c \
		hash/prime.c \
		hash/resize_hash.c \
		test/test.c \
		test/process_2_3args_test.c \
		test/process_binary.c \
		test/process_unary.c \
		test/tokenize_test.c \
		test/utils_test.c \

INCLUDES_FILE = shell.h

OBJS_FOLDERS = builtins editor editor/tabulator editor/history shell \
                shell/split shell/process hash test shell/jobs
OBJS = $(addprefix $(DIR_OBJ),$(SRCS:.c=.o))
OBJS_FOLDERS_BIS = $(addprefix $(DIR_OBJ),$(OBJS_FOLDERS))

all:	$(NAME) lib after_make

lib:
		@if !(make -q -C $(DIR_LIB)); then \
			rm -f $(OBJ); \
			rm -f $(NAME); \
			make -C $(DIR_LIB);\
		fi;

$(NAME): $(OBJS)
	@make -C $(DIR_LIB)
	@gcc -o $(NAME) $(OBJS) -L $(DIR_LIB) -lft -ltermcap #-fsanitize=address

$(DIR_OBJ)%.o: $(DIR_SRC)%.c  $(DIR_INC)/$(INCLUDES_FILE)
	@mkdir -p $(DIR_OBJ) $(OBJS_FOLDERS_BIS)
	@gcc -o $@ -c $< $(DIR_INC2) $(CFLAGS)
	@printf "\e[?25l\e[J$(PURPLE)Created $@ $(NOCOLOR)\r"

after_make:
		@printf "\e[0m\e[?25h"
clean:
	@rm -rf $(DIR_OBJ)
	@make clean -C $(DIR_LIB)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(DIR_LIB)

re: fclean all

# Personnal test
# <  echo ~ ~te~st" ~ '$USER  \""+\\$USER+$US\ER~$USERS' ~ t"e$USER \'~'' ""'`' ""' \' ""'" \'>
# <echo "test>
# <echo test\ {ENTER} ' {ENTER} test {ENTER} '>
# <echo 'test\'.
# echo tes't $USER te'st
# echo tes"t $USER te"st
# lancer minishell et <cd -> bash: cd: OLDPWD not set
# path avec lien <cd -L -L -P -L .>  --> pas de redi
# && <cd -L -P .> --> redi
# <mkdir test1> && <chmod 666 test1> && <cd test> --> Fail
# <mkdir test2> && <chmod 111 test2> && <cd test2> --> OK
# mkdir folder && cd folder && cd .. && rm -rf folder && cd -
# <cd \./> && pwd --> PWD et OLDPWD devrait avoir la meme valeur
# <cd \/.///> && env PWD && cd ..
# <cd ~///./folder//.//>
# cd ~bocal/Public --> {~} correspond à /Users et {~/} correpond à /Users/ythollete
# echo ~root
# cat * | ./minishell <-- pas a executer mais a protéger
# env -i ./minishell && unsetenv PATH && echo $HOME && cd ~
# ./minishell && unsetenv HOME && cd $random --> HOME not set
# ./minishell < "n'importe quel fichier"
# </> && <~> && </Users>
# ./minishell && ./minishell && ./minishell && CtrC && CtrlD && exit
# echo `ls\` --> ` && echo `ls\``
# echo "text" > file ; < file cat
# {echo test 1>/dev/ttys001 1>&2} --> la derniere redi est prit en compte et print test
# cat << EOF existing_file {ENTER} word1 {ENTER} EOF {ENTER}
# echo test >'&2' && cat "&2" --> fichier &2
# echo file > '&'
# {export tty=/dev/ttys001} {echo test > $tty} et car ttys001 recoit
# {echo test > "/dev/ttys001\\"} --> error avec {/dev/ttys001\\}
# echo test > file > /dev/ttys001 (le dernier est prit en compte mais file est créé)
# echo test > glob"{ENTER}file" --> test dans file {glob?file}
# echo test>file1>file2
# echo test>file1\>file2
# echo test>file1\\>file2
# echo test \22>&1 --> test 22 dans &1
# echo test > file_no_right
# echo test && {ENTER} \ {ENTER} \\ {ENTER} puis flèche du haut et histo == {echo test && \\}
# ; puis ;; (pas le meme msg d'erreur)
# {t &&} --> bquote
# >>>
# <!< { } - $?
# ls\ --> saut de ligne puis ls exec --> pas de saut de ligne dans l'histo
# mkdir ~/folder && cd ~/folder && chmod 111 ~/folder && ~/21sh/./21sh && echo file_not_found > file
# << EOF cat nofile ;; --> les EOF puis ;; puis erreur de cat
# ;; "test {ENTER} " --> les fermetures des quotes sont prio face au ;;
# echo test \1>/dev/ttys00\2 '1>/dev/ttys003' --> on envoi test et
# echo test > file && cat < file>>file2
# a=5 b=3 echo $a (variable local envoyé temporairement dans la cmd)
# echo test << "1" && test ; <<\2
# cat << "EO {ENTER} F" {ENTER} puis essayer de fermer
# heredoc puis Cltr-c et Ctrl-v
# cat <<t {ENTER} test {Ctrl-D} ->> heredoc stop mais test dans cat
# << \'"test"\\
# >oui<<EOF
# <<EOF<file_stdin
# <<EOF>file_stdout
# {test && w} et {test || w} --> test renvoi FAIL
# env -i env
# exit | ls --> ne doit pas exit
# setenv VAR file && echo no_var>'$VAR' && echo var>$VAR
# setenv VAR ambiguous_redirect > $VAR
# export VAR file && echo test >~/$VAR
# unsetenv $HOME && echo "pwd.h get the *pw_name" >~/file
# echo file_line > file && cat << EOF1 < file << EOF2 puis line1 \n EOF1 \n line2 \n EOF2 --> dernier element avec bash et en suivant l'ordre pour zsh
# exit 1arg 2arg --> no exit
# cat <&\2
# echo test >folder/unfind_folder/file
# echo test >&0
# echo test > file | cat -->stdou prio sur pipe
# echo test | cat < file --> file écrase le pipe
# exit 2>file
# exit | test
# exit 1 2 --> too many arg et pas d'exit
# exit t --> exit mais pas msg "numeric arg required"
# / et /tmp --> "Is directory"
# auteur
# ls doesnotexist . >/dev/null 2>&1 (rien) et ls doesnotexist . 2>&1 >/dev/null (no such file or..)
# /Users/ythollet/42h/42sh -->exec et ~/42/42sh -->exec et 42sh -->pas exec
# a="1'2{ENTER}3" --> echo $a = 1'2 3
# "no'var"=command_not_found
# a={te"st}|ENTER|" --> a=$'{test}\n'
# 1=pasok mais a1=ok
# a={test --> ouvrir l'accolade et l'a fermer
# alias ls="echo noprint" && \ls --> ls est exec
# ls && cat || ls --> Ctrl-Z de cat --> ls s'execute
# cat &
# cat + Ctrl-Z puis ls
# mkfifo fifo && cat < fifo et avec autre shell : ls > fifo
# mkfifo fifo && ls >> fifo et lire fifo
# lorsque fifo est déjà en lecture ou ecriture avec un autre shell --> print error msg
# ls && exit &
# pwd && exit && ls & --> pwd mais pas d'exit ni ls
# echo ${} | wc --> les 2 sont exec
# echo ${} || echo ok ; echo ok
# echo ${} &&/|| wc --> fail pas de wc
# ls | echo ${} | wc &
# voir les valeurs de retour d'exit selon http://www.tldp.org/LDP/abs/html/exitcodes.html