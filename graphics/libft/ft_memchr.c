/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:32:06 by bsarai            #+#    #+#             */
/*   Updated: 2021/11/11 20:32:08 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	r;

	tmp = (unsigned char *) s;
	r = (unsigned char) c;
	while (n)
	{
		if (*tmp == r)
			return (tmp);
		tmp++;
		n--;
	}
	return (NULL);
}
