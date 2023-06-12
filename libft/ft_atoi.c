/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:00:28 by jsabound          #+#    #+#             */
/*   Updated: 2022/11/11 11:45:00 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int		sign;
	int		num;
	char	*str;

	str = (char *)nptr;
	sign = 1;
	num = 0;
	while ((*str == ' ') || (*str == '\t') || (*str == '\n')
		|| (*str == '\v') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str + 1 == '-' || *str + 1 == '+')
		return (0);
	else if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * sign);
}
