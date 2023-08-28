/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:01:42 by jsabound          #+#    #+#             */
/*   Updated: 2023/04/27 18:11:50 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include"ft_printf.h"

char	*ft_toupper_hexa(char *s)
{
	int	i;

	if (!s)
		return (s);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] > 96 && s[i] < 123)
			s[i] -= 32;
		i++;
	}
	return (s);
}

unsigned int	ft_printhexa(unsigned long p, int n)
{
	char	res[17];
	int		i;

	i = 0;
	while (p >= 16)
	{
		res[i] = "0123456789abcdef"[p % 16];
		p = p / 16;
		i++;
	}
	res[i] = "0123456789abcdef"[p];
	res[i + 1] = '\0';
	if (n)
		ft_toupper_hexa(res);
	while (i >= 0)
	{
		ft_putchar_fd(res[i], 1);
		i--;
	}
	return (ft_strlen(res));
}

void	ft_put_uint(unsigned int n, t_lenght *lst)
{
	if (n < 10)
	{
		ft_putchar_fd(n + 48, 1);
		lst->len += 1;
	}
	else
	{
		ft_put_uint(n / 10, lst);
		ft_put_uint(n % 10, lst);
	}
}

int	ft_intlen(int n)
{
	int	i;
	int	number;

	i = 0;
	if (!n)
		return (1);
	number = n;
	while (number)
	{
		number = number / 10;
		i++;
	}
	return (i);
}

const char	*ft_print(const char *format, t_lenght *lst)
{
	char	*next;

	next = ft_strchr(format, '%');
	if (next)
		lst->widht = next - format;
	else
		lst->widht = ft_strlen(format);
	write(2, format, lst->widht);
	lst->len += lst->widht;
	while (*format && *format != '%')
		format++;
	return (format);
}
