/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstdel.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:26:39 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:26:39 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "list.h"

/*
** Prend en paramètre l’adresse d’un pointeur sur un maillon et
** libère la mémoire de ce maillon et celle de tous ses successeurs
** l’un après l’autre avec del et free(3). Pour terminer,
** le pointeur sur le premier maillon maintenant libéré doit être
** mis à NULL
*/

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (alst)
	{
		while ((*alst)->next != NULL)
			ft_lstdelone(&(*alst)->next, del);
		ft_lstdelone(alst, del);
	}
}
