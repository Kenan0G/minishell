/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:13:30 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 15:54:11 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*exec_export(t_cmd *c_list, t_env *env_list)
{
	t_env	*temp;
	int		check;

	temp = NULL;
	check = 0;
	if (c_list->arg[1] == NULL)
		return (export(env_list), env_list);
	else if (c_list->arg[1][0] == '-')
		return (printf("export: %c%c: Invalid option\n", c_list->arg[1][0],
			c_list->arg[1][1]), env_list);
	exec_export_utils(c_list, env_list, temp, check);
	return (env_list);
}

void	exec_export_utils(t_cmd *c_list, t_env *env_list, t_env *temp,
		int check)
{
	int	lenght;
	int	i;

	i = 1;
	while (c_list->arg[i])
	{
		if (export_check(c_list->arg[i]))
		{
			check = 0;
			temp = env_list;
			lenght = export_utils_1(c_list->arg[i]);
			if (lenght == -1)
				my_lstadd_back_env(&env_list, my_lstnew_env(c_list->arg[i], 0));
			else
			{
				while (temp && check != 1)
				{
					check = export_utils_2(c_list->arg[i], lenght, temp);
					temp = temp->next;
				}
				export_utils_3(temp, check, env_list, c_list->arg[i]);
			}
		}
		i++;
	}
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

int	export_utils_2(char *arg, int lenght, t_env *temp)
{
	int	tmp;

	(void)lenght;
	tmp = get_lenght(temp->env, '=');
	if (!ft_strncmp(temp->env, arg, tmp))
	{
		if (temp->env)
		{
			free(temp->env);
			temp->env = NULL;
		}
		temp->env = ft_strdup(arg);
		temp->printable = 1;
		return (1);
	}
	return (0);
}

void	export_utils_3(t_env *temp, int check, t_env *env_list, char *str)
{
	if (temp == NULL && check == 0)
		my_lstadd_back_env(&env_list, my_lstnew_env(str, 1));
}
