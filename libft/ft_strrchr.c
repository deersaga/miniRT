/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:49:47 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/09 01:15:34 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	ssize_t	last;
	char	cc;

	last = -1;
	i = 0;
	cc = (char)c;
	while (s[i] != 0)
	{
		if (s[i] == cc)
			last = i;
		i++;
	}
	if (cc != 0 && last == -1)
		return (NULL);
	if (cc == 0)
		return ((char *)&s[i]);
	return ((char *)&s[last]);
}

/*
#include <stdio.h>
int main()
{
	char *result;
	char *s = "Hello";
	result = strrchr(s, 108);
	printf("%s\n", result);
}
*/