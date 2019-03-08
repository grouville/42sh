/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 18:26:19 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:26:19 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/maths.h"

/*
** Alloue (avec malloc(3)) et retourne une chaine de caractères
** “fraiche” terminée par un ’\0’ représentant l’entier n passé
** en paramètre. Les nombres négatifs doivent être gérés. Si l’allocation
** échoue, la fonction renvoie NULL.
**
** Remarque :
** ABS est une macro inclu dans libft.h
** l39 +48 pour correspondre au valeurs numeriques dans les tables ascii
*/

char	*ft_itoa(int n)
{
	char		*ret;
	int			len;
	long int	s_n;

	s_n = n;
	len = ft_lenint(n);
	if (!(ret = ft_strnew(len)))
		return (NULL);
	ret[len--] = '\0';
	if (!n)
		ret[len--] = '0';
	s_n = ABS(s_n);
	while (s_n)
	{
		ret[len--] = (s_n % 10) + '0';
		s_n /= 10;
	}
	if (n < 0)
		ret[0] = '-';
	return (ret);
}
