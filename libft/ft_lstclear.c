/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:03:21 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/07 20:54:35 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*next;

	if (!lst || !(*lst))
		return ;
	cur = *lst;
	next = cur->next;
	while (1)
	{
		ft_lstdelone(cur, del);
		if (next == NULL)
			break ;
		cur = next;
		next = cur->next;
	}
	*lst = 0;
}
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	lstdelone_f(void *d) {
	free(d);
}

int main()
{
	void (*po)(void *) = lstdelone_f;
	t_list *l = ft_lstnew(strdup("nyancat"));
	l->next = ft_lstnew(strdup("#TEST#"));
	ft_lstclear(&l, po);
	//write(2, "", 1);
	if (!l)
		printf("SUCCESS\n");
	else
		printf("FAILED\n");
}
*/