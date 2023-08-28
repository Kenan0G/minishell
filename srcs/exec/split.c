/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:43:18 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/27 17:56:07 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// static int ft_strlensep(char *str, char c, t_data *data)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = data->is;
// 	if (str[j] == c)
// 		j++;
// 	while (str[j] && str[j] != c)
// 	{
// 		j++;
// 		i++;
// 	}
// 	return (i);
// }

// static char *create_double_quote(char *str, t_data *data)
// {
// 	char *temp;
// 	int i;

// 	temp = malloc(sizeof(char) * ft_strlensep(str, '"', data) + 2);
// 	i = 0;
// 	while (str[data->is] )
// 	{
// 		temp[i] = str[data->is];
// 		i++;
// 		data->is++;
// 		if (str[data->is] == '"')
// 			break ;
// 	}
// 	data->is++;
// 	temp[i] = '\0';
// 	return (temp);
// }

// static char *create_simple_quote(char *str, t_data *data)
// {
// 	char *temp;
// 	int i;

// 	temp = malloc(sizeof(char) * ft_strlensep(str, '\'', data) + 2);
// 	i = 0;
// 	while (str[data->is] )
// 	{
// 		temp[i] = str[data->is];
// 		i++;
// 		data->is++;
// 		if (str[data->is] == '\'')
// 			break ;
// 	}
// 	data->is++;
// 	temp[i] = '\0';
// 	return (temp);
// }

static char *create_charset(char *str, char *charset, t_data *data)
{
	char *temp;
	int i;
	int	len;
	(void)charset;

	len = 1;
	i = data->is;
	while (str[i] == str[i + 1])
	{
		i++;
		len++;
	}
	temp = malloc(sizeof(char) * (len + 1));
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
	int		i;
	int		j;

	i = data->is;
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && !ft_ischarset(str[i], charset))
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

static char *create_word(char *str, char *charset, t_data *data)
{
	char *temp;
	int i;

	int len = wordlen(str, charset, data);
	temp = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (str[data->is] && str[data->is] != ' ' && str[data->is] != '\t' &&!ft_ischarset(str[data->is], charset))
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
	else if (i == 2 && c && c != ' ' && c != '\t' && c != '"' && c != '\'' && !ft_ischarset(c, charset))
		return (1);
	return (0);
}

int len_split(char *str, char *charset)
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
			if (!ft_ischarset(str[i], charset) && str[i] != ' ' && str[i] != '\t')
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
	// printf("malloc = %d\n\n", len + set);
	return (len + set);
}

// int len_split(char *str, char *charset)
// {
//         int len;
//         int i;

//         if (!str)
//                 return (0);
//         i = 0;
//         len = 0;
//         while (str[i])
// 		{
// 			if (str[i] == ' ')
// 			{
// 				len++;
// 				while (str[i] == ' ')
// 					i++;
// 			}
// 			if (ft_ischarset(str[i], charset))
// 			{
// 				len++;
// 				while (ft_ischarset(str[i], charset))
// 					i++;
// 			}
// 			i++;
//         }
// 		printf("len = %d\n", len);
//         return (len);
// }


char **mr_split(char *str, char *charset, t_data *data)
{
	char **split;
	int j;
	int malloc_len;

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
	// int k = 0;
	// while (split[k])
	// {
	// 	printf("%s\n", split[k]);
	// 	k++;
	// }
	return (split);
}

// <	in	cat	|	<<	l	cat	>	out



// a priori tt ce qui est en bas est reglé


// lensplit qui marche pas du tout
// malloc des create double simple quote et create charset ne fonctionne pas comme il faut
// strlensep aussi compte pas les guillemets ou les charset 
// mot  (espace/s a la fin)    ->espaces a la fin pris en compte
// quand il y a plusieurs charset collés il faut les separer
// quand il y a mot"text", les guillemets ne sont pas gerés