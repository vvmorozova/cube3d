/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:53:21 by bsarai            #+#    #+#             */
/*   Updated: 2021/11/09 09:53:24 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char **dst, char const *src, int start, int end);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;

	start = 0;
	if (!s1 || !set)
		return ((char *) s1);
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) && (s1[start]))
		start++;
	while ((ft_strchr(set, s1[end])) && end)
		end--;
	if (start < end)
		str = malloc (end - start + 2);
	else
		str = malloc (1);
	if (!str)
		return (NULL);
	ft_strcpy(&str, s1, start, end);
	return (str);
}

static void	ft_strcpy(char **dst, char const *src, int start, int end)
{
	int		i;
	char	*d;
	char	*s;

	i = 0;
	d = *dst;
	s = (char *)src;
	while (start <= end)
	{
		d[i] = s[start];
		i++;
		start++;
	}
	d[i] = '\0';
}
