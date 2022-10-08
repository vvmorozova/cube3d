/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:18:53 by bsarai            #+#    #+#             */
/*   Updated: 2021/11/11 20:18:57 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = malloc(ft_strlen(s1) + 1);
	if (!ret)
		return (NULL);
	tmp = (char *) s1;
	while (*tmp)
		ret[i++] = *tmp++;
	ret[i] = '\0';
	return (ret);
}
