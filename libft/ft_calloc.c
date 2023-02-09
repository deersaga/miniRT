/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:51:15 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/19 01:51:10 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count)
		if (size > SIZE_MAX / count)
			return (NULL);
	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	ptr = (void *)malloc((count * size));
	if (!ptr)
		return (NULL);
	ft_bzero((void *)ptr, count * size);
	return (ptr);
}

/*#include <stdio.h>
int main()
{
	unsigned char *s;
	s = calloc(10000000000000, 10);
	//char *t = "hsjakkfk";
	//int i = -1;
	if (s == NULL)
		printf("success\n");
	printf("%x\n", s[10000000000000]);
	//printf("failed\n");
	while(++i < 20)
	{
		printf("i %i %i\n", i, s[i] == 0);
	}
	printf("%s\n", t);
}*/