/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maths.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/13 19:07:34 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/13 19:07:34 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include "libft.h"

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_lenint(int n);
int		ft_lenint_base(uintmax_t nb, int base);
int		ft_sqrt(int nb);
char	*ft_utoa(unsigned long long value, unsigned int base);

int		ft_digitlen(intmax_t n);

#endif
