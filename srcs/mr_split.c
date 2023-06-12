/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 18:15:04 by kgezgin           #+#    #+#             */
/*   Updated: 2023/05/19 11:50:34 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int ft_isspace(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int ft_word_count(char *str, char *charset)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && ft_isspace(str[i], charset))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && !ft_isspace(str[i], charset))
			i++;
	}
	return (count);
}

static int ft_strlensep(char *str, char *charset)
{
	int i;

	i = 0;
	while (str[i] && !ft_isspace(str[i], charset))
		i++;
	return (i);
}

static char *ft_create_word(char *str, char *charset)
{
	char *word;
	int i;
	int len_word;

	i = 0;
	len_word = ft_strlensep(str, charset);
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

static char *ft_create_charset(char *str, int len_word)
{
	char *word;
	int i;

	i = 0;
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

char **mr_split(char *str, char *charset)
{
	char **split;
	int i;
	int j;

	split = malloc(sizeof(char *) * (ft_word_count(str, charset) + 1));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		
	}
	split[i] = NULL;
	return (split);
}
