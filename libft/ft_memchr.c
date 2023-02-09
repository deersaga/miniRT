/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:48:49 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/07 16:03:37 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sp;
	unsigned char	cc;

	sp = (unsigned char *)s;
	cc = (unsigned char)c;
	while (n && *sp != cc)
	{
		sp++;
		n--;
	}
	if (n != 0)
		return ((void *)sp);
	return (NULL);
}
