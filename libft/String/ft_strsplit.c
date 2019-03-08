/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:29:51 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:29:51 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
** Renvoi un tableau résultant de la découpe de {*s} par {c}
** Exemple :
** ft_strsplit("*salut*les***etudiants*", ’*’)
** --> ["salut", "les", "etudiants"]
*/

#include "string.h"

char			**ft_strsplit(char const *s, char c)
{
	size_t		k;
	size_t		j;
	size_t		i;
	char		**ret;

	i = 0;
	j = 0;
	if (!s || !(ret = (char **)ft_memalloc(sizeof(char *)
						* (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			k = 0;
			while (s[i + k] != '\0' && s[i + k] != c)
				k++;
			ret[j++] = ft_strsub(s, i, k);
			i += k;
		}
	}
	ret[j] = 0;
	return (ret);
}
