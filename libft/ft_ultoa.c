/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 03:22:16 by katakagi          #+#    #+#             */
/*   Updated: 2022/05/07 03:22:18 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
This function can convert
unsigned long to 2 ~ 16 base string.
*/
static size_t	get_size(unsigned long n, int base)
{
	size_t	size;

	size = 1;
	while (n / base != 0)
	{
		n /= base;
		size++;
	}
	return (size);
}

char	*ft_ultoa(unsigned long n, int base)
{
	char			*result;
	size_t			size;

	if (base < 2 || base > 16)
		return (NULL);
	size = get_size(n, base);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[size] = 0;
	while (n / base != 0)
	{
		result[--size] = BASE[n % base];
		n /= base;
	}
	result[--size] = BASE[n % base];
	return (result);
}
