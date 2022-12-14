/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:42:50 by bsarai            #+#    #+#             */
/*   Updated: 2021/11/09 12:07:15 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ret;
	unsigned long	i;

	i = 0;
	ret = (unsigned char *) s;
	while (i < n)
	{
		ret[i] = '\0';
		i++;
	}
}
