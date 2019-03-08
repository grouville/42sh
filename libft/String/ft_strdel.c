/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdel.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:28:35 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:28:35 by ythollet    ###    #+. /#+    ###.fr     */
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

void	ft_strdel(char **as)
{
	if (*as)
	{
		ft_bzero(*as, (size_t)ft_strlen(*as));
		free(*as);
		*as = NULL;
	}
}
