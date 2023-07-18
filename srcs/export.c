/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:13:30 by kgezgin           #+#    #+#             */
/*   Updated: 2023/07/18 15:27:33 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*exec_export(t_cmd *c_list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	(void)p_list;
	(void)data;
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
			return (env_list);
		while (temp)
		{
			check = export_utils_2(temp->env, c_list->arg[i], lenght);
			temp = temp->next;
		}
		export_utils_3(temp, check, env_list, c_list->arg[i]);
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

int	export_utils_2(char *env, char *arg, int lenght)
{
	if (!ft_strncmp(env, arg, lenght))
	{
		if (env)
			free (env);
		env = malloc(sizeof(char) * ft_strlen(arg) + 1);
		ft_strlcpy(env, arg, ft_strlen(arg) + 1);
		return (1);
	}
	return (0);
}

void	export_utils_3(t_env *temp, int check, t_env *env_list, char *str)
{	
	if (temp == NULL && check == 0)
		my_lstadd_back_env(&env_list, my_lstnew_env(str));
}