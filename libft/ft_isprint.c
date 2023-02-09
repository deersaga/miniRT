/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:43:29 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/23 07:32:17 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}

/*
#include <stdio.h>
int main()
{
	char s = 'A';
	char t = '1';
	char u = 'a';
	char r = '!';
	printf("arg 'A' result %i\n", ft_isascii(s));
	printf("arg '1' result %i\n", ft_isascii(t));
	printf("arg 'a' result %i\n", ft_isascii(u));
	printf("arg '!' result %i\n", ft_isascii(r));
}
*/