/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 23:50:40 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/09 02:55:06 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_storage(char **storage, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(storage[i]);
		i++;
	}
	free(storage);
	return (NULL);
}

static char	**make_storage(char **storage, const char *str, char sep)
{
	size_t	i;
	size_t	j;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != sep)
		{
			j = 0;
			while (str[i + j] != sep && str[i + j])
				j++;
			storage[count] = (char *)malloc((j + 1) * sizeof(char));
			if (!storage[count])
				return (free_storage(storage, count));
			ft_strlcpy(storage[count], &str[i], j + 1);
			count++;
			i += j;
		}
		else
			i++;
	}
	storage[count] = 0;
	return (storage);
}

char	**ft_split(char const *str, char sep)
{
	char		**storage;
	size_t		i;
	size_t		count;

	if (!str)
		return (NULL);
	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != sep && (str[i + 1] == sep || str[i + 1] == '\0'))
			count++;
		i++;
	}
	storage = (char **)malloc((count + 1) * sizeof(char *));
	if (!storage)
		return (NULL);
	return (make_storage(storage, str, sep));
}
/*
#include <stdio.h>
int main()
{
	char *s = "      split       this for   me  !       ";
	char **storage = ft_split(s, ' ');
	printf("%s\n", storage[0]);
	printf("%s\n", storage[1]);
	printf("%s\n", storage[2]);
	printf("%s\n", storage[3]);
	printf("%s\n", storage[4]);
	printf("%s\n", storage[5]);
	//printf("%s\n", storage[5]);
}
*/