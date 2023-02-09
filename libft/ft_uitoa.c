/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 03:20:57 by katakagi          #+#    #+#             */
/*   Updated: 2022/05/07 03:20:58 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
This function can convert
unsigned int to 2 ~ 16 base string.
*/
static size_t	get_size(unsigned int n, int base)
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

char	*ft_uitoa(unsigned int n, int base)
{
	char				*result;
	size_t				size;

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
