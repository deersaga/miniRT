/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:49:54 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/06 12:50:08 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

/*
#include <stdio.h>
int main()
{
	char s = 'A';
	char t = '1';
	printf("arg 'A' result %c\n", ft_tolower(s));
	printf("arg '1' result %c\n", ft_tolower(t));
}
*/