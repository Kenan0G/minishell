/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:06:24 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/25 17:47:50 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execution_loop(t_cmd *list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	t_cmd	*c_list;

	data->index_2 = 0;
	c_list = list;
	data->c_list_temp = &list;
	while (c_list)
	{
		if (c_list->is_ok)
		{
			loop_utils_1(&c_list, &p_list, data, &env_list);
			c_list = c_list->next;
			data->index++;
			data->index_2++;
		}
		else
		{	
			loop_utils_2(&list, &p_list, data, &env_list);
			c_list = c_list->next;
			data->index++;
		}
	}
}

void	loop_utils_1(t_cmd **c_list, t_parsed **p_list, t_data *data, t_env **env_list)
{
	t_cmd		*c_temp;
	t_parsed	*p_temp;
	t_env		*e_temp;
	
	c_temp = *c_list;
	p_temp = *p_list;
	e_temp = *env_list;
	data->previous_fd = data->fd_pipe[0];
	loop_utils_1_2(data, c_temp);
	// printf("data->index = %d\n", data->index);
	data->pid[data->index] = fork();
	if (data->pid[data->index] == 0)
	{
		// if (c_temp->command_int != EXPORT)
		redirections(c_temp, data);
		if (c_temp->command_int == COMMAND)
			get_path_and_exec(c_temp, p_temp, data, e_temp);
		else
		{
			exec_builtin(c_temp, p_temp, *env_list, data);
			free(data->pid);
			ft_free_all(data->c_list_temp, p_list, data, env_list);
			ft_free_env(env_list);
			exit (data->error_status);
		}
	}
	loop_utils_1_3(data);
}

void	loop_utils_1_2(t_data *data, t_cmd *c_temp)
{
	if (c_temp->next)
	{	
		if (pipe(data->fd_pipe) == -1)
			return (perror("Pipe"));
		if (c_temp->fd_in == 0)
			c_temp->fd_in = data->previous_fd;
		if (c_temp->fd_out == 0)
			c_temp->fd_out = data->fd_pipe[1];
	}
	else
	{
		if (c_temp->fd_in == 0)
			c_temp->fd_in = data->previous_fd;
		if (data->index_2 > 0)
			close(data->fd_pipe[1]);
	}
}

void	loop_utils_1_3(t_data *data)
{
	if (data->previous_fd > 0)
		close(data->previous_fd);
	if (data->fd_pipe[1] > 0)
		close (data->fd_pipe[1]);
}

void	loop_utils_2(t_cmd **list, t_parsed **p_list, t_data *data, t_env **env_list)
{
	data->previous_fd = 0;
	data->pid[data->index] = fork();
	if (data->pid[data->index] == 0)
	{
		ft_free_all(list, p_list, data, env_list);
		ft_free_env(env_list);
		free(data->pid);
		exit(1);
	}
}