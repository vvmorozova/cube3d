/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:09:02 by bsarai            #+#    #+#             */
/*   Updated: 2021/11/12 13:09:04 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_power(int nb);
static int	ft_len(int nb);

char	*ft_itoa(int n)
{
	char	*str;
	int		power;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_len(n);
	power = ft_power(n);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[i++] = '-';
		n = (-n);
	}
	while (power != 0)
	{
		str[i++] = n / power + 48;
		n %= power;
		power /= 10;
	}
	str[i] = '\0';
	return (str);
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

static int	ft_len(int nb)
{
	int	i;

	i = 1;
	if (nb < 0)
		i++;
	while (nb / 10 != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}
