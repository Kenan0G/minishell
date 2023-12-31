/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:46:14 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/08 15:41:33 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*exec_unset(t_cmd *c_list, t_env **env_list)
{
	int	i;

	i = 1;
	if (c_list->arg[1] && c_list->arg[1][0] == '-' && c_list->arg[1][1] != '\0')
	{
		printf("env: %c%c: Invalid option\n",
			c_list->arg[1][0], c_list->arg[1][1]);
		return (*env_list);
	}
	else if (c_list->arg[1] && c_list->arg[1][0] == '-'
			&& c_list->arg[1][1] == '\0')
		return (*env_list);
	while (c_list->arg[i])
	{
		if (export_check(c_list->arg[i]))
			unset_utils(c_list->arg[i], env_list);
		i++;
	}
	return (*env_list);
}

void	unset_utils(char *str, t_env **env_list)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = *env_list;
	while (current)
	{
		if (!ft_strncmp(current->env, str, ft_strlen(str))
			&& ft_strlen(str) == get_lenght(current->env, '='))
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->env);
			free(current);
			return ;
		}
		prev = current ;
		current = current->next;
	}
}

size_t	get_lenght(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}
