/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:55:37 by jsabound          #+#    #+#             */
/*   Updated: 2022/11/16 11:27:18 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*t;
	unsigned char	*s;

	if (src == dest || !n)
		return (dest);
	if (dest < src)
	{
		t = (unsigned char *)dest;
		s = (unsigned char *)src;
		while (n--)
			*t++ = *s++;
	}
	else
	{
		t = (unsigned char *)dest + (n - 1);
		s = (unsigned char *)src + (n - 1);
		while (n--)
			*t-- = *s--;
	}
	return (dest);
}
