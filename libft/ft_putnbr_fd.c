/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:53:26 by katakagi          #+#    #+#             */
/*   Updated: 2022/04/09 02:55:08 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_x_digit_fd(unsigned int n, int fd)
{
	char	msb;

	if (n / 10 > 0)
		print_x_digit_fd(n / 10, fd);
	msb = '0' + n % 10;
	ft_putchar_fd(msb, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (n < 0)
	{
		nbr = -1 * n;
		ft_putchar_fd('-', fd);
	}
	else
		nbr = n;
	print_x_digit_fd(nbr, fd);
}
