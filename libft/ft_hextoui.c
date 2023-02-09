/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 02:53:20 by katakagi          #+#    #+#             */
/*   Updated: 2022/05/28 21:30:58 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_lower_hex(const char *str)
{
	char	*num;
	int		i;

	num = ft_strdup(str);
	if (!num)
		return (NULL);
	i = 0;
	while (num[i])
	{
		num[i] = ft_tolower(str[i]);
		i++;
	}
	return (num);
}

unsigned int	ft_hextoui(const char *str)
{
	unsigned long long	result;
	char				*num;
	int					i;

	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'\
	|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (str[0] == '0' && str[1] == 'x')
		str += 2;
	else
		return (0);
	num = get_lower_hex(str);
	if (!num)
		return (0);
	i = -1;
	while (ft_strchr(BASE, num[++i]) - &BASE[0] != 16)
	{
		if (result * 16 > LLMAX || result * 16 + \
		(ft_strchr(BASE, num[i]) - &BASE[0]) > LLMAX)
			return (0);
		result = result * 16 + (ft_strchr(BASE, num[i]) - &BASE[0]);
	}
	free(num);
	return ((unsigned int)(result));
}
