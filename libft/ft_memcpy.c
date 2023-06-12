/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:44:57 by jsabound          #+#    #+#             */
/*   Updated: 2022/12/09 17:36:01 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*str;
	char		*res;

	if (!dest && !src)
		return (NULL);
	str = src;
	res = dest;
	i = 0;
	while (i < n)
	{
		res[i] = str[i];
		i++;
	}
	return (dest);
}
