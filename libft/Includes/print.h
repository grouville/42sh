/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/13 19:33:28 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/30 19:43:48 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "libft.h"

int		ft_putchar(int c);
int		ft_putchar_fd(char c, int fd);
int		ft_putnbr_signed(intmax_t nb);
int		ft_putnbr_unsigned(uintmax_t nb);
int		ft_putstr(char const *s);
int		ft_putstr_fd(char const *s, int fd);
int		ft_putwchar(wchar_t c);
int		ft_putwstr(wchar_t const *s);
int		ft_putchar_dup(char c, int i);
void	ft_putendl(const char *s);

#endif
