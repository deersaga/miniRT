/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:46:24 by susami            #+#    #+#             */
/*   Updated: 2023/02/02 10:47:02 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q miniRT 2>/dev/null | grep -E ' leak(s)? for ' -A 5");
}
