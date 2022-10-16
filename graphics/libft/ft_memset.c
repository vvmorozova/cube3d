/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:18:01 by bsarai            #+#    #+#             */
/*   Updated: 2021/11/09 11:18:03 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ret;
	unsigned char	character;

	ret = (unsigned char *)b;
	character = (unsigned char) c;
	while (len)
	{
		*ret = character;
		ret++;
		len--;
	}
	return (b);
}
