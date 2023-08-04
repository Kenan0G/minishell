/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_env_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:44:49 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/04 15:03:45 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

		// if (c_list->arg[i + 1] && c_list->quote_status[i + 1] == NO_QUOTE
		// 		&& c_list->quote_status[i] == NO_QUOTE)

void	exec_echo(t_cmd *c_list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (c_list->arg[i])
	{
		if (i == 1)
		{	
			while (c_list->arg[i] && !ft_strcmp(c_list->arg[i], "-n"))
		{
			newline = 0;
			i++;
		}	
		}
		if (c_list->arg[i])
		{		
			printf("%s", c_list->arg[i]);
			if (c_list->arg[i + 1])
				printf(" ");
		}
		if (!c_list->arg[i])
			break ;
		i++;
	}
	if (newline)
		printf("\n");
	free(data->pid);
	ft_free_all(&c_list, &p_list, data, NULL);
	ft_free_env(&env_list);
}

void	exec_env(t_cmd *c_list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	(void)p_list;
	(void)c_list;
	print_env(env_list);
	free(data->pid);
	ft_free_all(&c_list, &p_list, data, &env_list);
	ft_free_env(&env_list);
}

void	exec_exit(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	(void)p_list;
	(void)c_list;
	(void)data;
	printf("exec_exit\n");
	free(data->pid);
	ft_free_all(&c_list, &p_list, data, NULL);
	// exit (0);
}