/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:28:55 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:28:55 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
** Alloue (avec malloc(3)) et retourne une chaine de caractères
** “fraiche” terminée par un ’\0’ résultant de la concaténation
** de s1 et s2. Si l’allocation echoue, la fonction renvoie NULL.
**
** Param :
** 1.La chaine de caractères préfixe.
** 2.La chaine de caractère “fraiche” résultant de la concaténation
** des deux chaines.
**
** Remarque :
** ft_strnew se prend in +1 pour le '\0' en fin de chaine
*/

#include "string.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *retour;

	if (s1 && s2)
	{
		if (!(retour = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
			return (NULL);
		ft_strcpy(retour, s1);
		ft_strcat(retour, s2);
		return (retour);
	}
	return (NULL);
}
