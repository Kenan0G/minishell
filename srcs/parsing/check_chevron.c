/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chevron.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:40:11 by jsabound          #+#    #+#             */
/*   Updated: 2023/09/12 14:45:08 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_chevron_out(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			|| (str[i] == '>' && str[i + 1] == '>' && str[i + 3] == '>'))
		{
			printf("minishell: syntax error near unexpected token `>>'\n");
			return (2);
		}
		else if ((str[i] == '>' && str[i + 2] == '>') || (str[i] == '<' && str[i
					+ 2] == '>'))
		{
			printf("minishell: syntax error near unexpected token `>'\n");
			return (2);
		}
		i++;
	}
	return (0);
}

int	check_chevron_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			|| (str[i] == '<' && str[i + 1] == '<' && str[i + 3] == '<'))
		{
			printf("minishell: syntax error near unexpected token `<<'\n");
			return (2);
		}
		else if ((str[i] == '<' && str[i + 2] == '<') || (str[i] == '>' && str[i
					+ 2] == '<'))
		{
			printf("minishell: syntax error near unexpected token `<'\n");
			return (2);
		}
		i++;
	}
	return (0);
}
