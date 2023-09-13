/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:38:38 by jsabound          #+#    #+#             */
/*   Updated: 2023/09/13 13:05:16 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_double_quote(char *str)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i = skip_to_next_quote(str, i, '\'');
			if (!str[i])
				break ;
		}
		if (str[i] == '"')
		{
			res++;
			i = skip_to_next_quote(str, i, '"');
			if (!str[i])
				break ;
			res++;
		}
		i++;
	}
	return (check_res(res, str, 1));
}

int	skip_to_next_quote(char *str, int i, char c)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	check_res(int res, char *str, int bool)
{
	if (bool == 1)
	{
		if (res % 2)
		{
			printf("minishell : missing double quote\n");
			return (2);
		}
		if (check_simple_quote(str) == 2)
			return (2);
	}
	else
	{	
		if (res % 2)
		{
			printf("minishell : missing simple quote\n");
			return (2);
		}
	}
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
			i = skip_to_next_quote(str, i, '"');
			if (!str[i])
				break ;
		}
		if (str[i] == '\'')
		{
			simple++;
			i = skip_to_next_quote(str, i, '\'');
			if (!str[i])
				break ;
			simple++;
		}
		i++;
	}
	return (check_res(simple, str, 0));
}
