/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrnew.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/15 19:27:52 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/15 19:28:00 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/string.h"

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

wchar_t		*ft_wstrnew(size_t size)
{
	wchar_t	*str;

	if (!(str = (wchar_t *)ft_memalloc(size + 1)))
		return (NULL);
	return (str);
}
