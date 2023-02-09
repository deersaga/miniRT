/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:35:16 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/23 07:31:36 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') \
	|| (c >= '0' && c <= '9'));
}

/*
#include <stdio.h>
int main()
{
	char s = 'A';
	char t = '1';
	char u = 'a';
	char r = '!';
	printf("arg 'A' result %i\n", ft_isalnum(s));
	printf("arg '1' result %i\n", ft_isalnum(t));
	printf("arg 'a' result %i\n", ft_isalnum(u));
	printf("arg '!' result %i\n", ft_isalnum(r));
}
*/