/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/21 18:08:46 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/19 23:32:40 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "libft.h"

# define PRINTF_TYPE "sSpdDioOuUxXcC%br"
# define PRINTF_ALL_FIELDS "#0-+ *123456789.hljz"
# define PRINTF_FLAGS "-+0 #"
# define PRINTF_SIZE "hljz"
# define PRINTF_NUMBERS "0123456789"

typedef struct	s_pf_fields
{
	BOOL	diese;
	BOOL	zero;
	BOOL	moins;
	BOOL	plus;
	BOOL	space;
	BOOL	point;
	BOOL	size;
	BOOL	wldcrd_prec;
	BOOL	wldcrd_width;
	int		width;
	int		precision;
	char	type;
}				t_pf_fields;

typedef struct	s_pf_prints
{
	void		*data;
	int			space_bfr;
	int			space_aftr;
	int			zero_bfr;
	int			zero_aftr;
	int			plus;
	int			minus;
	int			space;
	int			zero_x;
	int			zero_x_up;
	int			free;
}				t_pf_prints;

int				ft_dprintf(int fd, const char *format, ...);
t_pf_fields		pf_fields_reset(void);
t_pf_fields		pf_parse(const char **format);
intmax_t		pf_type(va_list ap, t_pf_fields *fields);
t_pf_prints		pf_convert(intmax_t *data, t_pf_fields *fields);
int				pf_print_field(t_pf_prints *data_prt, t_pf_fields *fields,
								int fd);
t_pf_prints		pf_print_reset(void);
void			pf_parse_flags(t_pf_fields *fields, const char **format);
void			pf_parse_correct(t_pf_fields *fields, char type,
									const char *str);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               Convert by type                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_pf_prints		pf_cvt_s(t_pf_prints *data_prt, t_pf_fields *fields);
t_pf_prints		pf_cvt_c(t_pf_prints *data_prt, t_pf_fields *fields);
t_pf_prints		pf_cvt_diu(t_pf_prints *print, t_pf_fields *fields);
t_pf_prints		pf_cvt_xp(t_pf_prints *data_prt, t_pf_fields *fields);
t_pf_prints		pf_cvt_o(t_pf_prints *data_prt, t_pf_fields *fields);
t_pf_prints		pf_cvt_br(t_pf_prints *print, t_pf_fields *fields);

#endif
