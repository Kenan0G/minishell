/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:04:26 by jsabound          #+#    #+#             */
/*   Updated: 2022/11/18 16:31:52 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*strbig;

	i = 0;
	j = 0;
	strbig = (char *)big;
	if (*little == '\0')
		return (strbig);
	while (strbig[i] != '\0')
	{
		j = 0;
		while (little[j] == strbig[i] && i < len)
		{
			if (little[j + 1] == '\0')
				return (&strbig[i - j]);
			j++;
			i++;
		}
		i = i - j;
		i++;
	}
	return (NULL);
}
