/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:44:56 by jsabound          #+#    #+#             */
/*   Updated: 2022/12/28 19:39:47 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

const char	*ft_checkargs(va_list arg, const char *format, t_lenght *lst)
{
	if (*format == 'c' || *format == 's')
		ft_arg_1(format, arg, lst);
	else if (*format == 'p' || *format == 'u')
		ft_arg_2(format, arg, lst);
	else if (*format == 'x' || *format == 'X' || *format == '%')
		ft_arg_4(format, arg, lst);
	else if (*format == 'd' || *format == 'i')
		ft_arg_5(arg, lst);
	else
		return (NULL);
	format++;
	return (format);
}

int	ft_printf(const char *format, ...)
{
	va_list		arg;
	t_lenght	lst;

	va_start(arg, format);
	lst.len = 0;
	lst.widht = 0;
	while (*format)
	{
		if (*format == '%')
			format = ft_checkargs(arg, format + 1, &lst);
		else
			format = ft_print(format, &lst);
		if (!format)
		{
			ft_putstr_fd("null", 1);
			va_end(arg);
			return (lst.len);
		}
	}
	va_end(arg);
	return (lst.len);
}
