/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:13:30 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/16 13:43:30 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*exec_export(t_cmd *c_list, t_env *env_list)
{
	t_env	*temp;
	int		i;
	int		lenght;
	int		check;

	i = 1;
	while (c_list->arg[i])
	{
		check = 0;
		temp = env_list;
		lenght = export_utils_1(c_list->arg[i]);
		if (lenght == -1)
			my_lstadd_back_env(&env_list, my_lstnew_env(ft_strdup(c_list->arg[i]), 0));
		else
		{
			while (temp && check != 1)
			{
				check = export_utils_2(&temp->env, c_list->arg[i], lenght);
				temp = temp->next;
			}
			export_utils_3(temp, check, env_list, c_list->arg[i]);
		}
		i++;
	}
	return (env_list);
}

int	export_utils_1(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

int	export_utils_2(char **env, char *arg, int lenght)
{
	if (!ft_strncmp(*env, arg, lenght))
	{
		if (*env)
		{
			free (*env);
			*env = NULL;
		}
		*env = ft_strdup(arg);
		return (1);
	}
	return (0);
}

void	export_utils_3(t_env *temp, int check, t_env *env_list, char *str)
{	
	if (temp == NULL && check == 0)
		my_lstadd_back_env(&env_list, my_lstnew_env(ft_strdup(str), 1));
}