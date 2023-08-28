/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:06:50 by jsabound          #+#    #+#             */
/*   Updated: 2022/12/09 17:51:05 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

static int	ft_word_count(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && ft_isspace(str[i], c))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && !ft_isspace(str[i], c))
			i++;
	}
	return (count);
}

static int	ft_strlensep(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i], c))
		i++;
	return (i);
}

static char	*ft_create_word(char *str, char c)
{
	char	*word;
	int		i;
	int		len_word;

	i = 0;
	len_word = ft_strlensep(str, c);
	word = malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	split = malloc(sizeof(char *) * (ft_word_count(str, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && ft_isspace(*str, c))
			str++;
		if (*str != '\0')
		{
			split[i] = ft_create_word(str, c);
			i++;
		}
		while (*str != '\0' && !ft_isspace(*str, c))
			str++;
	}
	split[i] = NULL;
	return (split);
}
