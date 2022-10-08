/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:55:29 by bsarai            #+#    #+#             */
/*   Updated: 2021/11/09 12:55:30 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count(char *s, char c);
static char		*ft_cpy_word(char *s, char c);
static char		**ft_cpy_words(char *s, char c, int count);
static void		ft_free_words(char **words, int i);

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**ret;

	str = ft_strdup(s);
	if (!s || !str)
		return (NULL);
	ret = ft_cpy_words(str, c, ft_count(str, c));
	free(str);
	return (ret);
}

int	ft_count(char *s, char c)
{
	int	nb;

	nb = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			nb++;
			while (*s && *s != c)
				s++;
		}
	}
	return (nb);
}

static char	*ft_cpy_word(char *s, char c)
{
	char	*word;

	word = s;
	while (*s && *s != c)
		s++;
	*s = '\0';
	return (ft_strdup(word));
}

static char	**ft_cpy_words(char *s, char c, int count)
{
	char	**words;
	char	*word;
	int		i;

	words = (char **) malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		word = ft_cpy_word(s, c);
		if (!word)
		{
			ft_free_words(words, i);
			return (NULL);
		}
		words[i++] = word;
		s += (ft_strlen(word) + 1);
	}
	words[i] = NULL;
	return (words);
}

static	void	ft_free_words(char **words, int i)
{
	while (i)
	{
		free(words[i]);
		i--;
	}
	free((char **)words);
}
