/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:32:18 by susami            #+#    #+#             */
/*   Updated: 2023/02/09 21:22:17 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void	fatal_error(const char *loc, const char *msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (msg == NULL)
		perror(loc);
	else
	{
		write(STDERR_FILENO, loc, ft_strlen(loc));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	exit(1);
}
