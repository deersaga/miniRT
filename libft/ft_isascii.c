/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:40:23 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/23 07:31:56 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
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