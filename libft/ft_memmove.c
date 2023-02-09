/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:46:40 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/09 04:26:51 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dp;
	const unsigned char	*sp;

	dp = (unsigned char *)dest;
	sp = (const unsigned char *)src;
	if (dest < src)
	{
		while (n--)
			*dp++ = *sp++;
	}
	else if (dest > src)
	{
		dp = dp + n;
		sp = sp + n;
		while (n--)
			*(--dp) = *(--sp);
	}
	return ((void *)dest);
}

/*
#include <stdio.h>
int main()
{
	char *s = malloc(7);
	int i = -1;
	while(++i < 7)
		s[i] = i + 1;
	char *t = s + 2;
	ft_memmove(s, t, 1);
	i = -1;
	printf("HEre\n");
	while (++i < 7)
		printf("%i\n", s[i]);

	i = -1;
	while(++i < 7)
		s[i] = i + 1;
	t = s + 2;
	ft_memmove(t, s, 1);
	i = -1;
	printf("HEre\n");
	while (++i < 7)
		printf("%i\n", s[i]);
}
*/