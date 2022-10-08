/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:58:08 by bsarai            #+#    #+#             */
/*   Updated: 2021/11/13 17:58:10 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_minor(size_t dlen, size_t dstsize);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	ret_len;

	dlen = (size_t) ft_strlen(dst);
	ret_len = ft_minor(dlen, dstsize) + (size_t) ft_strlen(src);
	if (dlen < dstsize)
	{
		dst += dlen;
		dstsize -= dlen;
		while (*src && dstsize > 1)
		{
			*dst++ = *src++;
			dstsize--;
		}
		*dst = '\0';
	}
	return (ret_len);
}

size_t	ft_minor(size_t dlen, size_t dstsize)
{
	if (dlen < dstsize)
		return (dlen);
	else
		return (dstsize);
}
