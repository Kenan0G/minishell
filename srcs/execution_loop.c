/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:06:24 by kgezgin           #+#    #+#             */
/*   Updated: 2023/07/18 16:21:03 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execution_loop(t_cmd *list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	t_cmd	*c_list;

	data->index_2 = 0;
	c_list = list;
	while (c_list)
	{
		if (c_list->is_ok)
		{
			data->previous_fd = data->fd_pipe[0];
			if (c_list->next)
			{
				if (pipe(data->fd_pipe) == -1)
					return (perror("Pipe"));
				if (c_list->fd_in == 0)
					c_list->fd_in = data->previous_fd;
				if (c_list->fd_out == 0)
					c_list->fd_out = data->fd_pipe[1];
			}
			else
			{
				if (c_list->fd_in == 0)
					c_list->fd_in = data->previous_fd;
				if (data->index_2 > 0)
					close(data->fd_pipe[1]);
			}
			data->pid[data->index] = fork();
			if (data->pid[data->index] == 0)
			{
				if (c_list->command_int != EXPORT)
					redirections(c_list, data);
				if (c_list->command_int == COMMAND)
					get_path_and_exec(c_list, p_list, data, env_list);
				else
					exec_builtin(c_list, p_list, data, env_list);
			}
			if (data->previous_fd > 0)
				close(data->previous_fd);
			if (data->fd_pipe[1] > 0)
				close (data->fd_pipe[1]);
			c_list = c_list->next;
			data->index++;
			// loop_utils_1(c_list, p_list, data, env_list);
			data->index_2++;
		}
		else
		{
			data->previous_fd = 0;
			data->pid[data->index] = fork();
			if (data->pid[data->index] == 0)
			{
				ft_free_all(&list, &p_list, data, &env_list);
				free(data->pid);
				exit(0);
			}
			c_list = c_list->next;
			data->index++;
		}
	}
}

// void	loop_utils_1(t_cmd *c_list, t_parsed *p_list, t_data *data, t_env *env_list)
// {
// 	data->previous_fd = data->fd_pipe[0];
// 	if (c_list->next)
// 	{
// 		if (pipe(data->fd_pipe) == -1)
// 			return (perror("Pipe"));
// 		if (c_list->fd_in == 0)
// 			c_list->fd_in = data->previous_fd;
// 		if (c_list->fd_out == 0)
// 			c_list->fd_out = data->fd_pipe[1];
// 	}
// 	else
// 	{
// 		if (c_list->fd_in == 0)
// 			c_list->fd_in = data->previous_fd;
// 		if (data->index_2 > 0)
// 			close(data->fd_pipe[1]);
// 	}
// 		data->pid[data->index] = fork();
// 		if (data->pid[data->index] == 0)
// 		{
// 			if (c_list->command_int != EXPORT)
// 				redirections(c_list, data);
// 			if (c_list->command_int == COMMAND)
// 				get_path_and_exec(c_list, p_list, data, env_list);
// 			else
// 				exec_builtin(c_list, p_list, data, env_list);
// 		}
// 		if (data->previous_fd > 0)
// 			close(data->previous_fd);
// 		if (data->fd_pipe[1] > 0)
// 			close (data->fd_pipe[1]);
// 		c_list = c_list->next;
// 		data->index++;
// }
