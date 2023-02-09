/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:37:25 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/23 07:31:34 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/*
int main()
{
	char *s = "alphabetonly";
	char *t = "not only alphabet!";
	if (ft_str_is_alpha(s) == 1)
		printf("only alphabet\n");
	else
		printf("not only alphabet\n");
	if (ft_str_is_alpha(t) == 1)
		printf("only alphabet\n");
	else
		printf("not only alphabet\n");
}
*/