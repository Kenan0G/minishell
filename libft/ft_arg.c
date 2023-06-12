/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:59:58 by jsabound          #+#    #+#             */
/*   Updated: 2023/04/27 18:11:30 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include"ft_printf.h"

void	ft_arg_1(const char *format, va_list arg, t_lenght *lst)
{
	char	c;
	char	*s;

	if (*format == 'c')
	{
		c = va_arg(arg, int);
		lst->len += 1;
		ft_putchar_fd(c, 2);
	}
	else if (*format == 's')
	{
		s = va_arg(arg, char *);
		if (!s)
		{
			write (1, "(null)", 6);
			lst->len += 6;
			return ;
		}
		else
		{
			lst->len += ft_strlen(s);
			ft_putstr_fd(s, 2);
		}
	}
}

void	ft_arg_2(const char *format, va_list arg, t_lenght *lst)
{
	unsigned int	u;
	void			*p;
	unsigned long	ptr;

	if (*format == 'u')
	{
		u = va_arg(arg, unsigned int);
		ft_put_uint(u, lst);
	}
	else if (*format == 'p')
	{
		p = va_arg(arg, void *);
		ptr = (unsigned long)p;
		if (p == 0)
		{
			write(1, "(nil)", 5);
			lst->len += 5;
			return ;
		}
		write(1, "0x", 2);
		lst->len += (ft_printhexa(ptr, 0) + 2);
	}
}

void	ft_arg_4(const char *format, va_list arg, t_lenght *lst)
{
	unsigned int	x;

	if (*format == 'x')
	{
		x = va_arg(arg, unsigned int);
		lst->len += ft_printhexa(x, 0);
	}
	else if (*format == 'X')
	{
		x = va_arg(arg, unsigned int);
		lst->len += ft_printhexa(x, 1);
	}
	else if (*format == '%')
	{
		ft_putchar_fd('%', 1);
		lst->len += 1;
	}
}

void	ft_arg_5(va_list arg, t_lenght *lst)
{
	int	d;

	d = va_arg(arg, int);
	if (d == -2147483648)
	{	
		write (1, "-2147483648", 11);
		lst->len += 11;
		return ;
	}
	else if (d < 0)
	{
		ft_putchar_fd('-', 1);
		lst->len += 1;
		d *= (-1);
	}
	lst->len += ft_intlen(d);
	ft_putnbr_fd(d, 1);
}
