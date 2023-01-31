/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 02:24:06 by katakagi          #+#    #+#             */
/*   Updated: 2023/01/31 17:02:44 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_search_add(t_list **lst, int fd)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp->next != NULL)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (tmp->fd == fd)
		return (tmp);
	tmp->next = ft_lstnew(fd);
	return (tmp->next);
}

char	*end_fd(char *result, t_list *cur_list, t_list **list)
{
	t_list	*tmpl;

	if (*list == cur_list)
		*list = cur_list->next;
	else
	{
		tmpl = *list;
		while (tmpl->next != cur_list)
			tmpl = tmpl->next;
		tmpl->next = cur_list->next;
	}
	free(result);
	free(cur_list->buf);
	free(cur_list);
	return (NULL);
}

char	*return_line(char *result, char *nl_pos, char *buf)
{
	char	*tmp;

	*nl_pos = '\0';
	tmp = ft_strjoin(result, buf);
	free(result);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!result)
		return (NULL);
	ft_memmove(buf, nl_pos + 1, BUFFER_SIZE - (nl_pos + 1 - buf) + 1);
	return (result);
}

char	*read_line(int count, t_list *cur_list, char *result, t_list *list)
{
	char	*tmp;

	while (count > 0)
	{
		cur_list->buf[count] = '\0';
		tmp = (char *)ft_strchr(cur_list->buf, '\n');
		if (tmp)
			return (return_line(result, tmp, cur_list->buf));
		else
		{
			tmp = ft_strjoin(result, cur_list->buf);
			free(result);
			if (!tmp)
				return (NULL);
			result = tmp;
		}
		count = read(cur_list->fd, cur_list->buf, BUFFER_SIZE);
	}
	if ((result[0] == '\0' && count == 0) || count < 0 )
		return (end_fd(result, cur_list, &list));
	cur_list->buf[0] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*cur_list;
	char			*result;
	char			*nl_pos;
	int				count;

	if (fd < 0)
		return (NULL);
	if (!list)
		list = ft_lstnew(fd);
	cur_list = ft_search_add(&list, fd);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	nl_pos = (char *)ft_strchr(cur_list->buf, '\n');
	if (nl_pos)
		return (return_line(result, nl_pos, cur_list->buf));
	free(result);
	result = ft_strdup(cur_list->buf);
	if (!result)
		return (NULL);
	count = read(fd, cur_list->buf, BUFFER_SIZE);
	if ((result[0] == '\0' && count == 0) || count < 0 )
		return (end_fd(result, cur_list, &list));
	return (read_line(count, cur_list, result, list));
}

