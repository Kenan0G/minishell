/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: red <red@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 18:15:04 by kgezgin           #+#    #+#             */
/*   Updated: 2023/07/21 17:34:27 by red              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int ft_isspace(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int ft_strlensep(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char *create_double_quote(char *str, t_data *data)
{
	char *temp;
	int i;
	
	temp = malloc(sizeof(char) * ft_strlensep(str, '"') + 1);
	i =0;
	while (str[data->is])
	{
		temp[i] = str[data->is];
		i++;
		data->is++;
		if (str[data->is] == '"')
		{
			data->is++;
			break;
		}
	}
	temp[i] = '\0';
	return (temp);
}

static char *create_simple_quote(char *str, t_data *data)
{
	char *temp;
	int i;
	
	temp = malloc(sizeof(char) * ft_strlensep(str, '\'') + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (str[data->is])
	{
		temp[i] = str[data->is];
		data->is++;
		i++;
		if (str[data->is] == '\'')
		{
			data->is++;
			break;
		}
	}
	temp[i] = '\0';
	return (temp);
}

static char *create_charset(char *str, char *charset, t_data *data)
{
	char *temp;
	int i;

	i = 0;
	temp = malloc(sizeof(char) * ft_strlensep(str, ' ') + 1);
	while (str[data->is] && ft_isspace(str[data->is], charset))
	{
		temp[i] = str[data->is];
		data->is++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

static char *create_word(char *str, char *charset, t_data *data)
{
	char *temp;
	int i;

	temp = malloc(sizeof(char) * ft_strlensep(str, ' ') + 1);
	i = 0;
	while (str[data->is] && !ft_isspace(str[data->is], charset) && str[data->is] != ' ')
	{
		temp[i] = str[data->is];
		data->is++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

int len_split(char *str, char *charset)
{
	int len;
	int i;
	int quote;

	if (!str)
		return (0);
	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == ' ' || ft_isspace(str[i], charset))
			len++;
		if (str[i] == '"' || str[i] == '\'')
			quote++;
		i++;
	}
	len += quote / 2;
	return (len);
}

char **mr_split(char *str, char *charset, t_data *data)
{
	char **split;
	int j;

	data->is = 0;
	split = malloc(sizeof(char *) * len_split(str, charset) + 1);
	if (!split)
		return (NULL);
	j = 0;
	while (str[data->is])
	{
		while (str[data->is] == ' ')
			data->is++;
		if (str[data->is] == '"')
			split[j] = create_double_quote(str, data);
		else if (str[data->is] == '\'')
			split[j] = create_simple_quote(str, data);
		else if (ft_isspace(str[data->is], charset))
			split[j] = create_charset(str, charset, data);
		else
			split[j] = create_word(str, charset, data);
		j++;
	}
	split[j] = NULL;
	return (split);
}