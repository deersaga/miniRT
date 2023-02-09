/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:27:36 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/06 12:36:46 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

/*
#include <stdio.h>
int main()
{
	char s = 'a';
	char t = '1';
	printf("arg 'a' result %c\n", ft_toupper(s));
	printf("arg '1' result %c\n", ft_toupper(t));
}
*/