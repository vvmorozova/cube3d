/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:06:20 by bsarai            #+#    #+#             */
/*   Updated: 2021/11/12 13:06:22 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_power(int nb);

void	ft_putnbr_fd(int n, int fd)
{
	int		power;
	char	c;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			c = '-';
			n = (-n);
			write(fd, &c, 1);
		}
		power = ft_power(n);
		while (power != 0)
		{
			c = n / power + 48;
			write(fd, &c, 1);
			n %= power;
			power /= 10;
		}
	}
}

static int	ft_power(int nb)
{
	int	pw;

	pw = 1;
	while (nb / 10 != 0)
	{
		pw *= 10;
		nb /= 10;
	}
	return (pw);
}
