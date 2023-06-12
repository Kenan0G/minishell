/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:42:24 by jsabound          #+#    #+#             */
/*   Updated: 2022/12/09 17:52:15 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s_1;
	int		i;
	int		j;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	j = 0;
	while (s1[i] != '\0' && ft_isspace(s1[i], set))
		i++;
	while (s1[i] != '\0' && ft_isspace(s1[len - j - 1], set) && i < len)
		j++;
	s_1 = ft_substr(s1, i, (len - j - i));
	return (s_1);
}
