/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 03:22:25 by katakagi          #+#    #+#             */
/*   Updated: 2022/05/07 03:22:27 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(long n, int base)
{
	size_t	size;

	size = 1;
	if (n < 0)
		size++;
	while (n / base != 0)
	{
		n /= base;
		size++;
	}
	return (size);
}

char	*ft_ltoa(long n, int base)
{
	unsigned long	un;
	char			*result;
	size_t			size;

	if (base < 2 || base > 16)
		return (NULL);
	size = get_size(n, base);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		un = n * -1;
		result[0] = '-';
	}
	else
		un = n;
	result[size] = 0;
	while (un / base != 0)
	{
		result[--size] = BASE[un % base];
		un /= base;
	}
	result[--size] = BASE[un % base];
	return (result);
}
