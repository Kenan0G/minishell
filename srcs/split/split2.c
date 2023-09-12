/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:58:16 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 20:18:02 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_word2(t_data *data, char *str, char *temp, int i)
{
	if (str[data->is] == '"')
	{
		temp[i] = str[data->is];
		data->is++;
		i++;
		while (str[data->is] != '"')
		{
			temp[i] = str[data->is];
			data->is++;
			i++;
		}
	}
	return (i);
}

int	create_word3(t_data *data, char *str, char *temp, int i)
{
	if (str[data->is] == '\'')
	{
		temp[i] = str[data->is];
		data->is++;
		i++;
		while (str[data->is] != '\'')
		{
			temp[i] = str[data->is];
			data->is++;
			i++;
		}
	}
	return (i);
}

int	not_charset_or_quote(char c, char *charset, int i)
{
	if (i == 1 && c && c != ' ' && c != '\t' && !ft_ischarset(c, charset))
		return (1);
	else if (i == 2 && c && c != ' ' && c != '\t' && c != '"' && c != '\''
		&& !ft_ischarset(c, charset))
		return (1);
	return (0);
}

int	len_split(char *str, char *charset, t_data *data)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	data->len = not_charset_or_quote(str[i], charset, 1);
	while (str[i])
	{
		data->is_quote = len_split2(data->is_quote, str[i]);
		i = len_split3(data, str, i, charset);
		if (ft_ischarset(str[i], charset) && data->is_quote == 0)
		{
			data->set++;
			while (str[i] == str[i + 1])
				i++;
			if (not_charset_or_quote(str[i + 1], charset, 1))
				data->len++;
		}
		i++;
	}
	return (data->len + data->set);
}

int	len_split2(int is_quote, char c)
{
	if (c == '"' && is_quote == 0)
		is_quote = 1;
	else if (c == '\'' && is_quote == 0)
		is_quote = 2;
	else if (c == '\'' && is_quote == 2)
		is_quote = 0;
	else if (c == '"' && is_quote == 1)
		is_quote = 0;
	return (is_quote);
}
