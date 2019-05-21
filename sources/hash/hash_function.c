/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 18:02:22 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 14:30:17 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

/*
*** - Aim of the function :
*** -  Prime is raised to the power of len
*/

long		ft_exponent(int prime, int len)
{
	double		nb;
	int			i;

	i = -1;
	nb = 1;
	while (++i < len)
		nb = nb * prime;
	return (nb);
}

/*
*** - Aim of the function :
*** -  returns the index resulting the hash function
*** - takes into parameter the size of the table and a prime number
*** - larger than the alphabet size (in ASCII, so prime > 128)
*/

int			ft_hash_generic(char *str, int prime, int size_table)
{
	long	index;
	int		i;
	int		len;

	index = 0;
	i = -1;
	len = ft_strlen(str);
	while (++i < len)
	{
		index += (long)ft_exponent(prime, len - (i + 1)) * str[i];
		index = index % size_table;
	}
	return ((int)index);
}

/*
*** - Aim of the function :
*** - return an index that manages collisions
*** - by rehashing using a different prime number,
*** - the index of the attempt + 1 to avoid luckless 0 index on the
*** - (attempt * (hash_b)) when hash_b == 0 that would nullify the
*** - purpose of the rehash
*/

int			ft_get_hash(char *str, int size_table, int attempt)
{
	int	hash_a;
	int	hash_b;

	hash_a = ft_hash_generic(str, HT_PRIME_1, size_table);
	hash_b = ft_hash_generic(str, HT_PRIME_2, size_table);
	return ((hash_a + (attempt * (hash_b + 1))) % size_table);
}

void		check_path_loop(char **path_env, char **path, char **str,
				int *count)
{
	int		j;
	char	*join_slash;
	char	*join_cmd;

	j = 0;
	while (path_env[j])
	{
		join_slash = ft_strjoin(path_env[j], "/");
		join_cmd = ft_strjoin(join_slash, *str);
		free(join_slash);
		if (access(join_cmd, F_OK) == 0)
		{
			if (*count >= 1)
				free(*path);
			*path = ft_strdup(join_cmd);
			(*count)++;
		}
		j++;
		free(join_cmd);
	}
	if (!(*path))
		*path = NULL;
}

int			ft_usage_is_good(char *limitor, char *str)
{
	int		i;
	int		n;
	BOOL	limitor_ok;

	i = 1;
	while (str[i])
	{
		limitor_ok = 0;
		n = 0;
		while (limitor[n])
		{
			if (str[i] == limitor[n++])
				limitor_ok = 1;
		}
		if (limitor_ok == 0)
			return (1);
		i++;
	}
	return (0);
}
