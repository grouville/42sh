/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strclr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:28:23 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:28:23 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Assigne la valeur ’\0’ à tous les caractères de la chaine passée
** en paramètre.
**
** Param :
** La chaine de caractères à clearer
**
** Retour :
** Rien
*/

void	ft_strclr(char *s)
{
	if (s)
	{
		while (*s)
			*s++ = '\0';
	}
}
