/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:37:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/08 15:38:54 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	export(t_env *env_list)
{
	int		i;
	int		j;
	char	**env;

	env = sort_env(env_list);
	i = 0;
	while (env[i])
	{
		j = 0;
		if (ft_strncmp(env[i], "_=", 2))
		{	
			printf("export ");
			display_export(env, i, j);
		}
		i++;
	}
	ft_free_map(env);
}

void	display_export(char **env, int i, int j)
{
	while (env[i][j])
	{	
		while (env[i][j] && env[i][j] != '=')
		{
			printf("%c", env[i][j]);
			j++;
		}
		if (!env[i][j])
		{
			printf("\n");
			break ;
		}
		printf("%c", env[i][j]);
		j++;
		printf("\"");
		while (env[i][j])
		{
			printf("%c", env[i][j]);
			j++;
		}
		printf("\"");
		printf("\n");
	}
}

char	**sort_env(t_env *env_list)
{
	int		i;
	int		j;
	char	**env;
	char	*temp;

	env = env_char(env_list);
	i = 0;
	j = 0;
	while (env[i])
	{
		j = i;
		while (env[j])
		{
			if (env[i][0] > env[j][0])
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

int	export_check(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (printf("export: '\": not a valid  identifier\n"), 0);
	else if (str[0] == '=')
		return (printf("export: %s : not a valid identifier\n", str), 0);
	else if (str[0] > 47 && str[0] < 58)
		return (printf("export: %s : not a valid identifier\n", str), 0);
	while (str[i] && str[i] != '=')
	{
		if (((str[i] >= 48) && (str[i] <= 57))
			|| ((str[i] >= 65) && (str[i] <= 90))
			|| ((str[i] >= 97) && (str[i] <= 122)) || (str[i] == '_'))
		i++;
		else
			return (printf("export: %s : not a valid identifier\n", str), 0);
	}
	return (1);
}
