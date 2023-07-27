/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:43:18 by kgezgin           #+#    #+#             */
/*   Updated: 2023/07/27 17:28:47 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static char *create_simple_quote(char *str, t_data *data)
// {
// 	char *temp;
// 	int i;
	
// 	temp = malloc(sizeof(char) * ft_strlensep(str, '\'', data) + 1);
// 	if (!temp)
// 		return (NULL);
// 	i = 0;
// 	while (str[data->is])
// 	{
// 		temp[i] = str[data->is];
// 		data->is++;
// 		i++;
// 		if (str[data->is] == '\'')
// 		{
// 			data->is++;
// 			break;
// 		}
// 	}
// 	temp[i] = '\0';
// 	return (temp);
// }

// int len_split(char *str, char *charset)
// {
// 	int len;
// 	int i;
// 	int quote;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	len = 0;
// 	quote = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ' ' || ft_ischarset(str[i], charset))
// 			len++;
// 		if (str[i] == '"' || str[i] == '\'')
// 			quote++;
// 		i++;
// 	}
// 	len += quote / 2;
// 	printf("lensplit = %d\n", len);
// 	return (len);
// }

// static int ft_strlensep(char *str, char c)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] && str[i] != c)
// 		i++;
// 	return (i);
// }

static int ft_ischarset(char c, char *charset)
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

static int ft_strlensep(char *str, char c, t_data *data)
{
	int i;
	int j;

	i = 0;
	j = data->is;
	if (str[j] == c)
		j++;
	while (str[j] && str[j] != c)
	{
		j++;
		i++;
	}
	return (i);
}

static char *create_double_quote(char *str, t_data *data)
{
	char *temp;
	int i;

	temp = malloc(sizeof(char) * ft_strlensep(str, '"', data) + 2);
	i = 0;
	while (str[data->is] )
	{
		temp[i] = str[data->is];
		i++;
		data->is++;
		if (str[data->is] == '"')
			break ;
	}
	data->is++;
	temp[i] = '\0';
	return (temp);
}

static char *create_simple_quote(char *str, t_data *data)
{
	char *temp;
	int i;

	temp = malloc(sizeof(char) * ft_strlensep(str, '\'', data) + 2);
	i = 0;
	while (str[data->is] )
	{
		temp[i] = str[data->is];
		i++;
		data->is++;
		if (str[data->is] == '\'')
			break ;
	}
	data->is++;
	temp[i] = '\0';
	return (temp);
}

// static char *create_charset(char *str, t_data *data)
// {
// 	char *temp;
// 	int i;

// 	i = 0;
// 	temp = malloc(sizeof(char) * 2);
// 	temp[i] = str[data->is];
// 	data->is++;
// 	i++;
// 	temp[i] = '\0';
// 	return (temp);
// }

static char *create_charset(char *str, char *charset, t_data *data)
{
	char *temp;
	int i;
	int	len;

	i = data->is;
	len = 0;
	while (ft_ischarset(str[i], charset))
	{
		i++;
		len++;
	}
	printf("len = %d\n", len);
	temp = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (str[data->is] && ft_ischarset(str[data->is], charset))
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

	i = data->is;
	j = 0;
	while (str[i] && str[i] != '"' && str[i] != '\'' && str[i] != ' ' && !ft_ischarset(str[i], charset))
	{
		i++;
		j++;
	}
	return (j);
}

static char *create_word(char *str, char *charset, t_data *data)
{
	char *temp;
	int i;

	temp = malloc(sizeof(char) * (wordlen(str, charset, data) + 1));
	i = 0;
	while (str[data->is] && str[data->is] != '"' && str[data->is] != '\''
			&& str[data->is] != ' ' && !ft_ischarset(str[data->is], charset))
	{
		temp[i] = str[data->is];
		data->is++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

int	not_charset_or_quote(char c, char *charset, int i)
{
	if (i == 1 && c && c != '"' && c != '\'' && !ft_ischarset(c, charset))
		return (1);
	else if (i == 2 && c && c != ' ' && c != '"' && c != '\'' && !ft_ischarset(c, charset))
		return (1);
	return (0);
}

int len_split(char *str, char *charset)
{
	int	len;
	int	set;
	int	i;

	if (!str)
		return (0);
	i = 0;
	set = 0;
	while (str[i] == ' ')
		i++;
	len = not_charset_or_quote(str[i], charset, 1);
	while (str[i])
	{
		while (str[i] == ' ')
		{
			i++;
			if (!str[i])
				return (/*printf("lensplit = %d\n\n", len + set), */len + set);
			if (not_charset_or_quote(str[i], charset, 2))
					len++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
			len++;
			if (not_charset_or_quote(str[i + 1], charset, 2))
				len++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			len++;
			if (not_charset_or_quote(str[i + 1], charset, 2))
				len++;
		}
		if (ft_ischarset(str[i], charset))
		{
			set++;
			if (not_charset_or_quote(str[i + 1], charset, 2))
				len++;
		}
		i++;
	}
	// printf("lensplit = %d\n\n", len + set);
	return (len + set);
}


char **mr_split(char *str, char *charset, t_data *data)
{
	char **split;
	int j;

	data->is = 0;
	split = malloc(sizeof(char *) * (len_split(str, charset) + 1));
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
		else if (ft_ischarset(str[data->is], charset))
			split[j] = create_charset(str, charset, data);
		else
			split[j] = create_word(str, charset, data);
		j++;
		while (str[data->is] == ' ')
			data->is++;
	}
	split[j] = NULL;
	return (split);
}




// a priori tt ce qui est en bas est reglé


// lensplit qui marche pas du tout
// malloc des create double simple quote et create charset ne fonctionne pas comme il faut
// strlensep aussi compte pas les guillemets ou les charset 
// mot  (espace/s a la fin)    ->espaces a la fin pris en compte
// quand il y a plusieurs charset collés il faut les separer
// quand il y a mot"text", les guillemets ne sont pas gerés