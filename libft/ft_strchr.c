/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:57:26 by jsabound          #+#    #+#             */
/*   Updated: 2022/11/14 18:13:17 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*src;

	src = (char *)s;
	while (*src)
	{
		if (*src == (char) c)
			return (src);
		src++;
	}
	if (*src == (char) c)
		return (src);
	return (NULL);
}
