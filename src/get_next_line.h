/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 02:18:18 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/22 08:26:28 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				fd;
	char			*buf;
	struct s_list	*next;
}	t_list;

void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
t_list	*ft_lstnew(int fd);
t_list	*ft_search_add(t_list **lst, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*end_fd(char *result, t_list *cur_list, t_list **list);
char	*return_line(char *result, char *nl_pos, char *buf);
char	*read_line(int count, t_list *cur_list, char *result, t_list *list);
char	*get_next_line(int fd);

#endif