/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:44:49 by kgezgin           #+#    #+#             */
/*   Updated: 2023/07/18 14:45:52 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_echo(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (c_list->arg[i])
	{
		if (i == 1 && !ft_strcmp(c_list->arg[1], "-n"))
			newline = 0;
		else
		{
			printf("%s", c_list->arg[i]);
			if (c_list->arg[i + 1])
				printf(" ");
		}
		i++;
	}
	if (newline)
		printf("\n");
	free(data->pid);
	ft_free_all(&c_list, &p_list, data, NULL);
}

void	exec_env(t_cmd *c_list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	(void)p_list;
	(void)c_list;
	print_env(env_list);
	free(data->pid);
	ft_free_all(&c_list, &p_list, data, &env_list);
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