/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:23:51 by jsabound          #+#    #+#             */
/*   Updated: 2022/11/16 13:31:33 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(int n, int len, int sign)
{
	char			*str;
	unsigned int	x;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (sign)
	{
		*str = '-';
		x = -n;
	}
	else
		x = n;
	str[len] = '\0';
	len--;
	while (len >= sign)
	{
		str[len] = (x % 10) + 48;
		x = x / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		temp;
	int		sign;

	len = 0;
	sign = 0;
	if (n < 0)
	{
		len++;
		sign++;
	}
	temp = n;
	while (temp != 0)
	{
		temp = temp / 10;
		len++;
	}
	if (n == 0)
		len++;
	return (ft_convert(n, len, sign));
}
