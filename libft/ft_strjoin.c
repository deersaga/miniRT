/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:51:37 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/12 09:11:31 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	cat_start;

	i = 0;
	while (dest[i] != '\0')
		i++;
	cat_start = i;
	while (src[i - cat_start] != '\0')
	{
		dest[i] = src[i - cat_start];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size] != '\0')
	{
		size++;
	}
	return (size);
}*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = (char *)malloc(size * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[0] = '\0';
	ft_strcat(ptr, s1);
	ft_strcat(ptr, s2);
	return (ptr);
}

/*
#include <stdio.h>
int main()
{
	//char *a[] = {"apple", "grape","pine"};
	char *ptr = ft_strjoin("apple ", "pine");
	printf("%s", ptr);
	system("leaks a.out");
}
*/
