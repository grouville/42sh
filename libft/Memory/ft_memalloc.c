/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:26:55 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:26:55 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "memory.h"

/*
** Alloue (avec malloc(3)) et retourne une zone de mémoire
** “fraiche”. La mémoire allouée est initialisée à 0. Si l’allocation
** échoue, la fonction renvoie NULL.
*/

void	*ft_memalloc(size_t size)
{
	void	*mlc;

	if (!(mlc = (void *)malloc(sizeof(void) * size)))
		return (NULL);
	ft_bzero(mlc, size);
	return (mlc);
}
