/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:48:42 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/23 06:59:56 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_sign(const char *sign)
{
	if (*sign == '-')
	{
		sign++;
		return (-1);
	}
	else if (*sign == '+')
	{
		sign++;
		return (1);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					minus;

	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'\
	|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	minus = check_sign(str);
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result * 10 > LLMAX || result * 10 + (*str) - '0' > LLMAX)
		{
			if (minus > 0)
				return (-1);
			return (0);
		}
		result = result * 10 + (*str++) - '0';
	}
	return ((int)(minus * (long long)result));
}

/*int	ft_atoi(const char *str)
{
	size_t	i;
	long	result;
	int		minus;

	i = 0;
	minus = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'\
	|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (minus * result);
}*/

/*
#include <stdio.h>
int main()
{
	int i = ft_atoi("  ---+-+--1504a3");
	printf("%d\n", i);

}
*/