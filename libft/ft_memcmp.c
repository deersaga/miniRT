/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:48:54 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/06 12:48:56 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	n = n + 1;
	while (--n && *us1 == *us2)
	{
		us1++;
		us2++;
	}
	if (n != 0)
		return ((int)(*us1 - *us2));
	return (0);
}

/*
#include <stdio.h>
int main()
{
	char *s1 = "Hello";
	char *s2 = "Hello";
	int r = ft_memcmp(s1, s2, 5);
	printf("%i\n", r);
}
*/