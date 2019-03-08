/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   char.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/13 18:52:28 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/24 01:45:37 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CHAR_H

# define CHAR_H

# include "libft.h"

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isprint(int c);
int		ft_isspace(char c);
int		ft_isupper(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_nbrchar(char *str, char c);
int		ft_size_wchar(wchar_t w);
char	*ft_chardup(char c, int dup);

#endif
