/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:45:01 by bsarai            #+#    #+#             */
/*   Updated: 2021/10/26 12:45:03 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*r;
	char	a;
	char	*adress;

	r = (char *) s;
	a = (char) c;
	adress = NULL;
	while (*r)
	{
		if (*r == a)
			adress = r;
		r++;
	}
	if (a == '\0')
		return (r);
	return (adress);
}
