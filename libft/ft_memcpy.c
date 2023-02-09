/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:46:23 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/09 04:26:35 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dp;
	const unsigned char	*sp;

	dp = (unsigned char *)dest;
	sp = (const unsigned char *)src;
	if (dp == sp)
		return ((void *)dest);
	while (n--)
		*dp++ = *sp++;
	return ((void *)dest);
}

/*
#include <stdio.h>
int main()
{
	char *s = malloc(6);
	char *t = "12\0 34";
	s = ft_memcpy(s, t, 4);
	int i = -1;
	while (++i < 6)
		printf("%i\n", s[i]);
}
*/