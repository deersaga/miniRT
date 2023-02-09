/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:47:28 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/07 16:14:49 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (dest != NULL)
	{
		if (size != 0)
		{
			while (src[i] != '\0' && i < size - 1)
			{
				dest[i] = src[i];
				i++;
			}
			dest[i] = '\0';
		}
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

/*
#include <stdio.h>
#include <string.h>
int main()
{
	char dest[1600] = "add";
	char *src = "he";
	unsigned int i = ft_strlcpy(dest, src, 4);
	printf("%d\n", i);
	printf("%s\n", dest);

	char dest2[1600] = "add";
	char *src2 = "he";
	unsigned int i2 = strlcpy(dest2, src2, 4);
	printf("%d\n", i2);
	printf("%s\n", dest2);
}
*/