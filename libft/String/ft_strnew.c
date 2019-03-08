/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:29:39 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:29:39 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Alloue (avec malloc(3)) et retourne une chaine de caractère
** “fraiche” terminée par un ’\0’. Chaque caractère de la chaine
** est initialisé à ’\0’. Si l’allocation echoue, la fonction renvoie
** NULL
**
** Param :
** La taille de la chaine de caractères à allouer
**
** Retour :
** La chaine de caractères allouée et initialisée à 0.
*/

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char *)ft_memalloc(size + 1)))
		return (NULL);
	return (str);
}
