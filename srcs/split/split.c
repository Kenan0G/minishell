/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:43:18 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 12:30:56 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_ischarset(char c, char *charset)
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

static char	*create_charset(char *str, char *charset, t_data *data)
{
	char	*temp;
	int		i;
	int		len;

	(void)charset;
	len = 1;
	i = data->is;
	while (str[i] == str[i + 1])
	{
		i++;
		len++;
	}
	temp = malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	i = 0;
	temp[i] = str[data->is];
	data->is++;
	i++;
	while (str[data->is] && (str[data->is] == str[data->is - 1]))
	{
		temp[i] = str[data->is];
		data->is++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

int	wordlen(char *str, char *charset, t_data *data)
{
	int	i;
	int	j;

	i = data->is;
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && !ft_ischarset(str[i],
			charset))
	{
		if (str[i] == '"')
		{
			i++;
			j++;
			while (str[i] != '"')
			{
				i++;
				j++;
			}
		}
		else if (str[i] == '\'')
		{
			i++;
			j++;
			while (str[i] != '\'')
			{
				i++;
				j++;
			}
		}
		i++;
		j++;
	}
	return (j);
}

static char	*create_word(char *str, char *charset, t_data *data)
{
	char	*temp;
	int		i;
	int		len;

	len = wordlen(str, charset, data);
	temp = malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (str[data->is] && str[data->is] != ' ' && str[data->is] != '\t'
		&& !ft_ischarset(str[data->is], charset))
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
		else if (str[data->is] == '\'')
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
		temp[i] = str[data->is];
		data->is++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
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

int	len_split(char *str, char *charset)
{
	int	len;
	int	set;
	int	i;
	int	is_quote;

	if (!str)
		return (0);
	i = 0;
	set = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	len = not_charset_or_quote(str[i], charset, 1);
	is_quote = 0;
	while (str[i])
	{
		if (str[i] == '"' && is_quote == 0)
			is_quote = 1;
		else if (str[i] == '\'' && is_quote == 0)
			is_quote = 2;
		else if (str[i] == '\'' && is_quote == 2)
			is_quote = 0;
		else if (str[i] == '"' && is_quote == 1)
			is_quote = 0;
		while ((str[i] == ' ' || str[i] == '\t') && is_quote == 0)
		{
			i++;
			if (!str[i])
				return (len + set);
			if (!ft_ischarset(str[i], charset) && str[i] != ' '
				&& str[i] != '\t')
			{
				if (str[i] == '"' && is_quote == 0)
					is_quote = 1;
				else if (str[i] == '\'' && is_quote == 0)
					is_quote = 2;
				len++;
			}
		}
		if (ft_ischarset(str[i], charset) && is_quote == 0)
		{
			set++;
			while (str[i] == str[i + 1])
				i++;
			if (not_charset_or_quote(str[i + 1], charset, 1))
				len++;
		}
		i++;
	}
	return (len + set);
}

char	**mr_split(char *str, char *charset, t_data *data)
{
	char	**split;
	int		j;
	int		malloc_len;

	data->is = 0;
	malloc_len = len_split(str, charset) + 1;
	split = malloc(sizeof(char *) * malloc_len);
	if (!split)
		return (NULL);
	j = 0;
	while (str[data->is] && malloc_len > 1)
	{
		while (str[data->is] == ' ' || str[data->is] == '\t')
			data->is++;
		if (ft_ischarset(str[data->is], charset))
			split[j] = create_charset(str, charset, data);
		else
			split[j] = create_word(str, charset, data);
		j++;
		while (str[data->is] == ' ' || str[data->is] == '\t')
			data->is++;
	}
	split[j] = NULL;
	return (split);
}
