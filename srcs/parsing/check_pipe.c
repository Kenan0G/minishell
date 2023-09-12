/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:39:17 by jsabound          #+#    #+#             */
/*   Updated: 2023/09/12 15:42:21 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipe(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '|' && str[i])
	{
		if ((str[i + 1] == '|' && str[i] == '>') || (str[i + 1] == '|'
				&& str[i] == '<'))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (2);
		}
		i++;
	}
	i = check_pipe2(str);
	if (!i)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (2);
	}
	if (check_between_pipe(str) == 2)
		return (2);
	return (0);
}

int	check_pipe2(char *str)
{
	int	i;
	int	x;
	int	j;

	x = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			x = 0;
			j = 0;
			while (str[j] && str[j] != '|')
			{
				if (str[j] && str[j] != ' ' && str[j] != '\t')
					x++;
				j++;
			}
		}
		i++;
	}
	return (x);
}

int	check_pipe3(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '|' && str[i + 1] == '|')
		{
			printf("minishell: syntax error near unexpected token `||'\n");
			return (2);
		}
		i++;
	}
	return (0);
}

int	check_between_pipe(char *str)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (str[i] && str[i] != '|')
		i++;
	if (!str[i])
		return (0);
	i++;
	while (str[i] != '|' && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			x++;
		i++;
	}
	if (!x)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (2);
	}
	return (0);
}
