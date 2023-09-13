/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:00:28 by jsabound          #+#    #+#             */
/*   Updated: 2023/09/13 15:40:08 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*too_long(char *str, long long int *num)
{
	while (*str >= '0' && *str <= '9')
	{
		*num = (*num * 10) + (*str - '0');
		str++;
	}
	return (str);
}

long long int	ft_atoi(const char *nptr)
{
	long long int	num;
	int				sign;
	char			*str;

	str = (char *)nptr;
	sign = 1;
	num = 0;
	if (*str + 1 == '-' || *str + 1 == '+')
		return (0);
	else if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	str = too_long(str, &num);
	num = num * sign;
	return ((int)num);
}
