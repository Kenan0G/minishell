/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:17:15 by jsabound          #+#    #+#             */
/*   Updated: 2022/12/09 17:56:32 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_malloc(size_t new_len)
{
	char	*str;

	str = malloc(sizeof(char) * new_len);
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || !s || !len || len < 1)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (len > ft_strlen(s))
		i = ft_strlen(s) + 1;
	if (len < ft_strlen(s))
		i = len + 1;
	if (len == ft_strlen(s))
		i = ft_strlen(s) - start + 1;
	str = ft_malloc(i);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s[start], i);
	return (str);
}
