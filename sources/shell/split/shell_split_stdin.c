/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_split_heredoc.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/18 16:14:04 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/18 16:14:04 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
** hrdc = NULL lors du premier heredoc
** le dernier ret[i] est à -1 pour indiquer qu'il n'est pas rempli
*/

char	**add_stdin(char **hrdc)
{
	char	**ret;
	int		i;

	i = 0;
	while (hrdc && hrdc[i] != NULL)
		i++;
	if (!(ret = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (hrdc && hrdc[i] != NULL)
	{
		if ((int)hrdc[i] == -1 || (int)hrdc[i] == -2)
			ret[i] = (char *)hrdc[i];
		else
		{
			ret[i] = ft_strdup(hrdc[i]);
			ft_strdel(&hrdc[i]);
		}
		i++;
	}
	if (hrdc)
		free(hrdc);
	ret[i] = (char *)-1;
	ret[i + 1] = NULL;
	return (ret);
}

/*
** sub la valeur dans stdin et recolle les 2 morceaux avec i au milieu
*/

int		shell_get_stdin(char ***ptn_stdin, char **arg, int i)
{
	int		len;
	char	quote;
	char	*bfr;
	char	*aft;

	*ptn_stdin = add_stdin(*ptn_stdin);
	shell_stdin_sub(arg, i + 1, ptn_stdin);
	(*arg)[i++] = '\0';
	quote = ft_strchr("\"'", (*arg)[i]) ? (*arg)[i] : (char)' ';
	len = len_stdin(*arg + i, quote);
	bfr = ft_strdup(*arg);
	aft = ft_strdup(*arg + i + len);
	ft_strdel(arg);
	*arg = ft_strjoin(bfr, aft);
	i = ft_strlen(bfr);
	ft_strdel(&bfr);
	ft_strdel(&aft);
	return (i);
}

int		shell_get_hrdc(char **arg, int i, t_cmd *cmd)
{
	int		last;
	char	quote;
	int		len;
	char	*tmp;

	cmd->hrdc = add_stdin(cmd->hrdc);
	shell_stdin_sub(arg, i + 2, &cmd->hrdc);
	(*arg)[i] = '\0';
	i += 2;
	quote = ft_strchr("\"'", (*arg)[i]) ? (*arg)[i] : (char)' ';
	len = len_stdin(*arg + i, quote);
	tmp = ft_strcutword(arg, i, len);
	ft_strdel(&tmp);
	cmd->input = add_stdin(cmd->input);
	last = 0;
	while ((cmd->input)[last] != NULL)
		last++;
	cmd->input[last - 1] = (cmd->process).stdin_send;
	return (i - 2);
}

int 	shell_get_stdin_send(char **arg, int i, t_cmd *cmd)
{
	int		len;
	char	quote;
	char 	*tmp;

	tmp = ft_strcutword(arg, i, 3);
	ft_strdel(&tmp);
	quote = ft_strchr("\"'", (*arg)[i]) ? (*arg)[i] : (char)' ';
	len = len_stdin(*arg + i, quote);
	if (len > 0)
	{
		tmp = ft_strcutword(arg, i, len);
		cmd->process.stdin_send = ft_strjoin(tmp, "\n");
		ft_strdel(&tmp);
	}
	else
		cmd->process.stdin_send = (char *)-2;
	return (i);
}

/*
** {hrdc[i] et std_in[i]} peuvent valoir soit :
** 	* une string
**  * -1 si non rempli (lors de la création/ajout)
**  * -2 si la chaine de char se trouve dans le prochain arg
**  * -3 pour être indiqué comme rempli par l'utilisateur
**
** (cmd->process).stdin_send (dont son adresse sera rentré dans **input) prend
** la valeur -1 pour ne pas stopper la lecture de stdin et prendra la valeur
** rentré par user
*/

void	shell_std_in(char **arg, char quote, t_cmd *cmd)
{
	int		i;

	complete_all_stdin(arg, quote, cmd);
	i = (quote == ' ' || (*arg)[0] == '\0') ? 0 : 1;
	while (*arg && (*arg)[i])
	{
		if ((*arg)[i] == '\\' && ft_strlen(*arg) >= (i + 2) && quote != '\'')
			i += 2;
		if (ft_strchr("'\"", (*arg)[i]) && quote == ' ')
			quote = (*arg)[i];
		else if ((*arg)[i] == quote && quote != ' ')
			quote = ' ';
		if (triple_chevrons(*arg + i) && quote == ' ')
			i = shell_get_stdin_send(arg, i, cmd);
		if (quote == ' ' && (*arg)[i] == '<' && (*arg)[i + 1] == '<')
		{
			(cmd->process).stdin_send = (char *)-1;
			i = shell_get_hrdc(arg, i, cmd);
		}
		else if (quote == ' ' && (*arg)[i] == '<')
			i = shell_get_stdin(&cmd->input, arg, i);
		else
			i += ((*arg)[i]) ? 1 : 0;
	}
}

/*
** Note de fin :
** L'inconvéniant d'attribuer des valeurs {-1}, {-2} et {-3} à un char* est
** qu'il nécessite un free particulier car valeurs numériques non malloc
*/
