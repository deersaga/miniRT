/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:51:26 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/07 20:47:28 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_size(int n)
{
	unsigned int	size;

	size = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		size++;
	}
	if (n < 0)
		size++;
	return (size);
}

char	*ft_itoa(int n)
{
	unsigned int	i;
	char			*result;
	unsigned int	size;

	size = get_size(n);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		i = n * -1;
		result[0] = '-';
	}
	else
		i = n;
	result[size] = 0;
	while (i / 10 != 0)
	{
		result[--size] = '0' + i % 10;
		i /= 10;
	}
	result[--size] = '0' + i % 10;
	return (result);
}

/*
#include <stdio.h>
int main()
{
	int i = -2147483648;
	char *s = ft_itoa(i);
	printf("%s\n", s);

}
*/