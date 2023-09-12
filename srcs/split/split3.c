/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:58:34 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 20:18:07 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_ischarset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	len_split3(t_data *data, char *str, int i, char *charset)
{
	while ((str[i] == ' ' || str[i] == '\t') && data->is_quote == 0)
	{
		i++;
		if (!str[i])
			return (data->len + data->set);
		if (!ft_ischarset(str[i], charset) && str[i] != ' ' && str[i] != '\t')
		{
			if (str[i] == '"' && data->is_quote == 0)
				data->is_quote = 1;
			else if (str[i] == '\'' && data->is_quote == 0)
				data->is_quote = 2;
			data->len++;
		}
	}
	return (i);
}
