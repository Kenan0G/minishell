/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:54:30 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/28 19:37:27 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_isspace(char c, char *charset)
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

static int	ft_strlensep(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

char	**mr_split(char *str, char *charset)
{
	char	**split;
	int		i;
	int		j;
	int		k;

	split = malloc(sizeof(char *) * 987978);
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (ft_isspace(str[i], charset))
		{
			k = 0;
			split[j] = malloc(sizeof(char) * ft_strlensep(&str[i]));
			while (str[i] && ft_isspace(str[i], charset))
			{
				split[j][k] = str[i];
				i++;
				k++;
			}
			j++;
		}
		while (str[i] == ' ')
			i++;
		if (!ft_isspace(str[i], charset))
		{
			k = 0;
			split[j] = malloc(sizeof(char) * ft_strlensep(&str[i]));
			while (str[i] && !ft_isspace(str[i], charset) && str[i] != ' ')
			{
				split[j][k] = str[i];
				i++;
				k++;
			}
			j++;
		}
		while (str[i] == ' ')
			i++;
	}
	split[i] = NULL;
	return (split);
}

void	get_env(t_data *data)
{
	t_env	*temp;
	int		i;

	temp = malloc(sizeof(t_env));
	if (!temp)
		return ;
	i = 0;
	data->envp = temp;
	while (data->env[i])
	{
		temp->env = NULL;
		temp->env = ft_strjoin(temp->env, data->env[i]);
		if (!data->env[i + 1])
			temp->next = NULL;
		else
		{
			temp->next = malloc(sizeof(t_env));
			if (!temp->next)
				return ;
			temp = temp->next;
		}
		i++;
	}
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	char	**splited;
	
	
// }