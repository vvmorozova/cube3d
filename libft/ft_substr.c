/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:03:30 by bsarai            #+#    #+#             */
/*   Updated: 2021/11/09 08:03:34 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned long	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) + 1 <= start)
		len = 0;
	if (len >= ft_strlen(s) - start)
		len = (size_t) ft_strlen(s) - start;
	substring = malloc (len + 1);
	if (substring)
	{
		while (i < len)
		{
			if (start < ft_strlen(s))
				substring[i] = s[start];
			else
				substring[i] = '\0';
			start++;
			i++;
		}
		substring[i] = '\0';
	}
	return (substring);
}
