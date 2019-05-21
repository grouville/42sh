/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tools2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/11 01:53:07 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/16 08:23:05 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

char	**ft_arrjoin(char **arr1, char **arr2)
{
	int		cursor_arrs;
	int		cursor_all_env;
	char	**all_env;

	cursor_arrs = 0;
	cursor_all_env = 0;
	all_env = malloc(sizeof(char *) * (ft_arrlen(arr1) + ft_arrlen(arr2) + 1));
	while (arr1[cursor_arrs])
		all_env[cursor_all_env++] = ft_strdup(arr1[cursor_arrs++]);
	cursor_arrs = 0;
	while (arr2[cursor_arrs])
		all_env[cursor_all_env++] = ft_strdup(arr2[cursor_arrs++]);
	all_env[cursor_all_env] = NULL;
	return (all_env);
}
