/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:42:46 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/23 07:31:54 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*
#include <stdio.h>
int main()
{
	char s = 'A';
	char t = '1';
	char u = 'a';
	char r = '!';
	printf("arg 'A' result %i\n", ft_isdigit(s));
	printf("arg '1' result %i\n", ft_isdigit(t));
	printf("arg 'a' result %i\n", ft_isdigit(u));
	printf("arg '!' result %i\n", ft_isdigit(r));
}
*/