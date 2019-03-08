/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:30:05 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:30:05 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/string.h"

/*
** Renvoi une copie fraiche de {*s} sans espace
** On considère comme espaces blancs les caractères ’ ’, ’\n’ et ’\t’.
*/

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	bgn;
	size_t	end;

	bgn = 0;
	if (!s)
		return (NULL);
	while ((s[bgn] == '\t' || s[bgn] == '\n' || s[bgn] == ' ') && s[bgn])
		bgn++;
	if (s[bgn] == '\0')
		return (ft_strnew(1));
	end = ft_strlen(s) - 1;
	while ((s[end] == '\t' || s[end] == '\n' || s[end] == ' ') && s[end])
		end--;
	end = end - bgn + 1;
	str = ft_strsub(s, bgn, end);
	return (str);
}
