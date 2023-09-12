/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:38:38 by jsabound          #+#    #+#             */
/*   Updated: 2023/09/12 20:13:50 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_double_quote(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				break ;
		}
		if (str[i] == '"')
		{
			i++;
			res++;
			while (str[i] && str[i] != '"')
				i++;
			if (!str[i])
				break ;
			res++;
		}
		i++;
	}
	if (res % 2)
	{
		printf("minishell : missing double quote\n");
		return (2);
	}
	if (check_simple_quote(str) == 2)
		return (2);
	return (0);
}

int	check_simple_quote(char *str)
{
	int	i;
	int	simple;

	i = 0;
	simple = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (!str[i])
				break ;
		}
		if (str[i] == '\'')
		{
			i++;
			simple++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				break ;
			simple++;
		}
		i++;
	}
	if (simple % 2)
	{
		printf("minishell : missing simple quote\n");
		return (2);
	}
	return (0);
}
