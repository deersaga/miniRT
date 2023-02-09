/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:51:43 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/19 02:25:42 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	int	i;
	int	j;
	int	m;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0' && n--)
	{
		if (str[i] != to_find[0])
		{
			i++;
			continue ;
		}
		j = i;
		m = n;
		while (str[i] == to_find[i - j] && m--)
		{
			i++;
			if (to_find[i - j] == '\0')
				return (&str[j]);
		}
		i = j + 1;
	}
	return (0);
}

static char	*strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != 0)
		i++;
	if (c != 0 && s[i] == 0)
		return (NULL);
	return ((char *)&s[i]);
}*/

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ret;

	if (!s)
		return (NULL);
	if (*s == '\0' || !set)
		return (ft_strdup(s));
	start = 0;
	end = ft_strlen(s);
	while (ft_strchr(set, s[start]) != NULL)
		start++;
	while (ft_strchr(set, s[end]) != NULL && end > start)
		end--;
	if (end == start)
	{
		return (ft_substr(s, start, 1));
	}
	ret = ft_substr(s, start, end - start + 1);
	return (ret);
}

/*
#include <stdio.h>
int main()
{
	//char s[50] = "";
	char *t;
	char *s = (char *)malloc(10);
	char *set = (char *)malloc(10);
	set[0] = '0';
	set[1] = '1';
	set[9] = 0;
	for (int i = 0; i < 10; i++)
	{
		s[i] = '0' + i;
	}
	t = ft_strtrim(s, "");

	printf("%s\n", t);
	free(t);
	free(set);
	free(s);

}*/