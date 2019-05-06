/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 15:14:05 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 16:28:22 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

/*
*** - Enum for the tok of "-d" :
*** - T_B is for option -b
*** - T_LL is for option -L
*** - 1x "B" --> Lowercase in the option
*** - 2x "L" --> Uppercase in the option
*/

typedef enum			e_test_tok
{
	T_B,
	T_C,
	T_D,
	T_E,
	T_F,
	T_G,
	T_LL,
	T_P,
	T_R,
	T_SS,
	T_S,
	T_U,
	T_W,
	T_X,
	T_Z,
	T_SEQ,
	T_SNE,
	T_EQ,
	T_NE,
	T_GE,
	T_LT,
	T_LE,
	T_EXCLAM,
	T_WORDS,
	T_QUOTE,
}						t_test_tok;

/*
*** - Enum for the types :
*** - Not -> "!"
*** - Birany -> "="
*** - Unary -> "-d"
*** - Args -> Word
*/

typedef enum			e_type_test
{
	T_ARGS,
	T_NOT,
	T_BINARY,
	T_UNARY,
	T_EXPANSED,
}						t_type_test;

/*
*** - Struct used for the initialization
*** - of the array below
*/

typedef struct			s_args_tok
{
	char			*op;
	int				size;
	t_test_tok		tok;
	t_type_test		type;
}						t_args_tok;

/*
*** - Array used to facilitate the tokenization
*** - for the test command
*/

static const t_args_tok	g_args_tok[] = {
	{"-b", 2, T_B, T_UNARY},
	{"-c", 2, T_C, T_UNARY},
	{"-d", 2, T_D, T_UNARY},
	{"-e", 2, T_E, T_UNARY},
	{"-f", 2, T_F, T_UNARY},
	{"-g", 2, T_G, T_UNARY},
	{"-L", 2, T_LL, T_UNARY},
	{"-p", 2, T_P, T_UNARY},
	{"-r", 2, T_R, T_UNARY},
	{"-S", 2, T_SS, T_UNARY},
	{"-s", 2, T_S, T_UNARY},
	{"-u", 2, T_U, T_UNARY},
	{"-w", 2, T_W, T_UNARY},
	{"-x", 2, T_X, T_UNARY},
	{"-z", 2, T_Z, T_UNARY},
	{"=", 1, T_SEQ, T_BINARY},
	{"!=", 2, T_SNE, T_BINARY},
	{"-eq", 3, T_EQ, T_BINARY},
	{"-ne", 3, T_NE, T_BINARY},
	{"-ge", 3, T_GE, T_BINARY},
	{"-lt", 3, T_LT, T_BINARY},
	{"-le", 3, T_LE, T_BINARY},
	{"!", 1, T_EXCLAM, T_NOT},
	{NULL, 1, 0, 0}
};

/*
*** - Struct for the norm of the tokenize function
*/

typedef struct			s_tok_norm
{
	char			**cmd;
	char			**raw_cmd;
}						t_tok_norm;

/*
*** - test.c
*/

int						ft_builtin_test(char **cmd, char **raw_cmd);
int						process_exclam(int nb, int ret_in);

/*
*** - utils_test.c
*/

t_args_tok				**initialize_arr_tok(int len);
int						free_tokens(t_args_tok ***t, int len);
int						ft_len_array_char_test(char **av, char **raw_av);
int						is_real_str_after_expansion(char *cmd);

/*
*** - process_2_3args_test.c
*/

int						is_all(t_args_tok *t);
int						is_any(t_args_tok *t);
int						is_s_bin(t_args_tok *t);
int						ft_test_2_args(t_args_tok **t, int boul);
int						ft_test_3_args(t_args_tok **t, int boul);

/*
*** - process_binary.c
*/

int						process_binary(char *str1, t_test_tok tok, char *str2);

/*
*** - process_unary.c
*/

int						process_unary(t_test_tok tok, char *arg);

/*
*** - tokenize_test.c
*/

void					tokenize_test(char **cmd, t_args_tok ***t,
							char **raw_cmd);
int						ft_strdelint(char **str);

#endif
