/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:17:50 by red               #+#    #+#             */
/*   Updated: 2023/09/12 20:16:39 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check(char *str)
{
	if (check_pipe3(str))
		return (2);
	if (check_metacaractere(str))
		return (2);
	if (check_double_quote(str))
		return (2);
	if (check_pipe(str))
		return (2);
	if (check_first_char(str))
		return (2);
	return (0);
}

int	check_metacaractere(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == ')')
		{
			printf("minishell: syntax error near unexpected token `)'\n");
			return (2);
		}
		else if (str[i] == '(')
		{
			printf("minishell: syntax error near unexpected token `('\n");
			return (2);
		}
		i--;
	}
	if (check_metacaractere2(str) == 2)
		return (2);
	else
		return (0);
}

int	check_metacaractere2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '&' && str[i + 1] == '&')
		{
			printf("minishell: syntax error near unexpected token `&&'\n");
			return (2);
		}
		else if (str[i] == ';' && str[i + 1] == ';')
		{
			printf("minishell: syntax error near unexpected token `;;'\n");
			return (2);
		}
		if (check_metacaractere3(i, str) == 2)
			return (2);
		i++;
	}
	return (0);
}

int	check_metacaractere3(int i, char *str)
{
	if (str[i] == ';' && str[i + 1] != ';')
	{
		printf("minishell: syntax error near unexpected token `;'\n");
		return (2);
	}
	else if (str[i] == '&' && str[i + 1] != '&')
	{
		printf("minishell: syntax error near unexpected token `&'\n");
		return (2);
	}
	return (0);
}

int	check_first_char(char *str)
{
	if ((str[0] == '>' && !str[1]) || (str[0] == '<' && !str[1])
		|| (str[0] == '>' && str[1] == '>' && !str[2]) || (str[0] == '<'
			&& str[1] == '<' && !str[2]) || (str[0] == '<' && str[1] == '>'))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (2);
	}
	else
	{
		if (check_chevron_in(str) == 2)
			return (2);
		if (check_chevron_out(str) == 2)
			return (2);
	}
	return (0);
}
