/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 02:15:32 by katakagi          #+#    #+#             */
/*   Updated: 2023/01/31 17:02:18 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dp;
	const unsigned char	*sp;

	dp = (unsigned char *)dest;
	sp = (const unsigned char *)src;
	if (dest < src)
	{
		while (n--)
			*dp++ = *sp++;
	}
	else if (dest > src)
	{
		dp = dp + n;
		sp = sp + n;
		while (n--)
			*(--dp) = *(--sp);
	}
	return ((void *)dest);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	cc;

	cc = (char)c;
	i = 0;
	while (s[i] != cc && s[i] != 0)
		i++;
	if (cc != 0 && s[i] == 0)
		return (NULL);
	return ((char *)&s[i]);
}

char	*ft_strdup(const char *src)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len] != '\0')
		len++;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

t_list	*ft_lstnew(int fd)
{
	t_list	*new;
	size_t	i;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!new->buf)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		new->buf[i] = '\0';
		i++;
	}
	new->next = NULL;
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	char	*ptr;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	size = 1;
	i = 0;
	while (s1[i++] != '\0')
		size++;
	i = 0;
	while (s2[i++] != '\0')
		size++;
	ptr = (char *)malloc(size * sizeof(char));
	if (!ptr)
		return (NULL);
	tmp = ptr;
	while (size-- && *s1 != '\0')
		*tmp++ = *s1++;
	while (size--)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (ptr);
}
