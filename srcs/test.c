/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:54:30 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/16 13:35:45 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env(t_env *env_list, char **env)
{
	t_env	*temp;
	int		i;

	temp = malloc(sizeof(t_env));
	if (!temp)
		return (NULL);
	i = 0;
	env_list = temp;
	while (env[i])
	{
		temp->env = NULL;
		temp->env = ft_strdup(env[i]);
		temp->printable = 1;
		if (!env[i + 1])
			temp->next = NULL;
		else
		{
			temp->next = malloc(sizeof(t_env));
			if (!temp->next)
				return (NULL);
			temp = temp->next;
		}
		i++;
	}
	return (env_list);
}

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	char	**splited;
	
	
// }

