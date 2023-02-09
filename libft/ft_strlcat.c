/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:47:11 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/07 13:25:58 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dest[i] != '\0' && i < size)
		i++;
	j = i;
	if (i == size || size == 0)
	{
		while (src[i - j] != '\0')
			i++;
		return (i);
	}
	while (src[i - j] != '\0' && i < size - 1)
	{
		dest[i] = src[i - j];
		i++;
	}
	dest[i] = '\0';
	while (src[i - j] != '\0')
		i++;
	return (i);
}

/*
#include <stdio.h>
#include <string.h>
int main()
{
	char c[50];
	c[0] = '\0';
	char *b = "world";
	char *a = "";
	a = &c[0];
	unsigned int i = ft_strlcat(a, "Hello0", 6);
	printf("%s ", a);
	printf("%d\n", i);
	i = ft_strlcat(a, b, 8);
	printf("%s ", a);
	printf("%d\n", i);


	char c2[50];
	c2[0] = '\0';
	char *b2 = "world";
	char *a2 = "";
	a2 = &c2[0];
	unsigned int i2 = strlcat(a2, "Hello0", 6);
	printf("%s ", a2);
	printf("%d\n", i2);
	i2 = strlcat(a2, b2, 8);
	printf("%s ", a2);
	printf("%d\n", i2);
}
*/