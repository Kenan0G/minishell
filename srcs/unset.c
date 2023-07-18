/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:46:14 by kgezgin           #+#    #+#             */
/*   Updated: 2023/07/18 16:03:20 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *exec_unset(t_cmd *c_list, t_parsed *p_list, t_data *data, t_env **env_list)
{
	(void)p_list;
	(void)data;
	t_env *current;
	int i;

	i = 1;
	while (c_list->arg[i])
	{
		current = *env_list;
		unset_utils(current, c_list->arg[i], env_list);
		i++;
	}
	return (*env_list);
}

void	unset_utils(t_env *current, char *str, t_env **env_list)
{
	t_env *prev;

	prev = NULL;
	while (current)
	{
		if (!ft_strncmp(current->env, str, ft_strlen(str))
				&& ft_strlen(str) == get_lenght(current->env))
		{
			if (prev)
				prev->next = current->next;
			else
			{
				*env_list = current->next;
				prev = *env_list;
			}
			unset_utils_2(current);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	unset_utils_2(t_env *current)
{
	t_env *temp;

	temp = NULL;
	temp = current;
	current = current->next;
	free(temp);
	temp = NULL;
}
size_t	get_lenght(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}