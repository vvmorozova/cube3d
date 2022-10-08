/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:17:35 by bsarai            #+#    #+#             */
/*   Updated: 2021/10/26 11:17:38 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	a;
	char	*r;

	a = (char) c;
	r = (char *) s;
	while (*r)
	{
		if (*r == a)
		{
			return (r);
		}
		r++;
	}
	if (a == '\0')
		return (r);
	return (NULL);
}
