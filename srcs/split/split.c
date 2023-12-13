/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:43:18 by kgezgin           #+#    #+#             */
/*   Updated: 2023/12/13 13:50:56 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	return (create_charset2(data, str, i, temp));
}

char	*create_charset2(t_data *data, char *str, int i, char *temp)
{
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
	int		i;
	int		j;
	char	c;

	i = data->is;
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && !ft_ischarset(str[i],
			charset))
	{
		c = str[i];
		if (c == '"' || c == '\'')
		{
			i++;
			j++;
			while (str[i] != c)
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
		i = create_word2(data, str, temp, i);
		i = create_word3(data, str, temp, i);
		temp[i] = str[data->is];
		data->is++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	**mr_split(char *str, char *charset, t_data *data)
{
	char	**split;
	int		j;
	int		malloc_len;

	data->is = 0;
	malloc_len = len_split(str, charset, data) + 1;
	split = malloc(sizeof(char *) * malloc_len);
	if (!split)
		return (NULL);
	j = 0;
	while (str[data->is] && malloc_len > 1)
	{
		dprintf(2, "main while in split\n");
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
