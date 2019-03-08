/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:26:51 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:26:51 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/list.h"

/*
** Alloue (avec malloc(3)) et retourne un maillon “frais”. Les
** champs content et content_size du nouveau maillon sont
** initialisés par copie des paramètres de la fonction. Si le paramètre
** content est nul, le champs content est initialisé à
** NULL et le champs content_size est initialisé à 0 quelque
** soit la valeur du paramètre content_size. Le champ next
** est initialisé à NULL. Si l’allocation échoue, la fonction renvoie
** NULL.
**
** Param :
** 1.Le contenu à ajouter au nouveau maillon
** 2.La taille du contenu à ajouter au nouveau maillon
*/

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	list = (t_list*)malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	if (content == NULL)
	{
		list->content = NULL;
		list->content_size = 0;
	}
	else
	{
		list->content = malloc(content_size);
		if (list->content == NULL)
			return (NULL);
		ft_memcpy(list->content, content, content_size);
		list->content_size = content_size;
	}
	list->next = NULL;
	return (list);
}
