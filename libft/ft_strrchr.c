/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:06:09 by jsabound          #+#    #+#             */
/*   Updated: 2023/09/13 14:39:28 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*src;
	char	*oc;

	src = (char *)s;
	oc = NULL;
	while (*src)
	{
		if (*src == (char)c)
			oc = src;
		src++;
	}
	if (oc != NULL)
		return (oc);
	if (*src == (char)c)
		return (src);
	return (NULL);
}
