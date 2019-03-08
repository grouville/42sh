/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   string.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/13 19:41:55 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/16 08:22:10 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

/*
** Pouquoi n'est-il pas possible de deplacer stddef dans libft.h ?
*/
# include <stddef.h>
# include "libft.h"

char		*ft_strcat(char *dst, const char *src);
char		*ft_strcat_free(char *dst, const char *src);
char		*ft_strchr(const char *s, int c);
void		ft_strclr(char *s);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dst, const char *src);
void		ft_strdel(char **as);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_strlen(const char *str);
char		*ft_strncat(char *s1, const char *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strncpy(char *dst, const char *src, size_t len);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
char		*ft_strnew(size_t size);
char		*ft_strrev(char *str);
char		**ft_strsplit(char const *s, char c);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strsub_free(char *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s);
int			ft_wstrcmp(const wchar_t *s1, const wchar_t *s2);
wchar_t		*ft_wstrcpy(wchar_t *dst, const wchar_t *src);
void		ft_wstrdel(wchar_t **as);
wchar_t		*ft_wstrdup(const wchar_t *s1);
int			ft_wstrlen(const wchar_t *wstr);
wchar_t		*ft_wstrncpy(wchar_t *dst, const wchar_t *src, size_t len);
wchar_t		*ft_wstrnew(size_t size);
wchar_t		*ft_wstrsub(wchar_t const *s, unsigned int start, size_t len);
wchar_t		*ft_wstrsub_free(wchar_t *s, unsigned int start, size_t len);
char		*ft_strjoin_mltp(int n, ...);
char		*ft_rmvpath(char *str);
void		ft_strdelchar(char **str, char c);
int			ft_strjoin_free(char **s1, const char *s2);
int			ft_strnbr(const char *str);
void		ft_char_join_free(char c, char **str);

#endif
