/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:49:00 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/09 04:24:27 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	cc;

	cc = (char)c;
	i = 0;
	while (s[i] != cc && s[i] != 0)
		i++;
	if (cc != 0 && s[i] == 0)
		return (NULL);
	return ((char *)&s[i]);
}

/*
#include "string.h"
#include <stdio.h>
int main()
{
	//char *result;
	char *s = NULL;// "Hello";
	char *result = strchr(s, 0);
	//if (result == NULL)
	//	printf("%x\n", result[0]);
	//printf("%s\n", result);
}
*/