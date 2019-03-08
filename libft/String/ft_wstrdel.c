/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_wstrdel.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/17 13:30:22 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/17 13:30:26 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "string.h"

/*
** Prend en paramètre l’adresse d’une chaine de caractères qui
** doit être libérée avec free(3) et son pointeur mis à NULL.
**
** Param :
** L’adresse de la chaine de caractère dont il faut libérer la mé-
** moire et mettre le pointeur à NULL
**
** Retour :
** Rien
*/

void	ft_wstrdel(wchar_t **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}
