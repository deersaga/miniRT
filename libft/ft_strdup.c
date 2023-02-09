/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:41:29 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/11 21:06:15 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*ptr;

	ptr = (char *)malloc((ft_strlen((const char *)src) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strcpy(ptr, src);
	return (ptr);
}

/*
#include <stdio.h>
int main()
{
	char *a = "HEllo World";
	char *b = ft_strdup(a);
	printf("%s", b);
}
*/