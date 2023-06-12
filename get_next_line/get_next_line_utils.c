/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:04:20 by kgezgin           #+#    #+#             */
/*   Updated: 2023/03/09 13:40:04 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	my_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*my_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	if (!s1)
		s1 = my_calloc(sizeof(char), 1);
	if (!s2)
		return (NULL);
	str = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

void	*my_calloc(size_t count, size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	s = malloc(count * size);
	if (!s)
		return (NULL);
	while (i < count * size)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

char	*my_strchr(char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (&s[i]);
	}
	return (0);
}
