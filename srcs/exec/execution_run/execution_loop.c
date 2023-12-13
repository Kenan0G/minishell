/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:06:24 by kgezgin           #+#    #+#             */
/*   Updated: 2023/12/13 13:34:06 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execution_loop(t_cmd *list, t_parsed *p_list, t_data *data,
		t_env *env_list)
{
	t_cmd	*c_list;

	data->index_2 = 0;
	c_list = list;
	data->c_list_adress = &list;
	while (c_list)
	{
		setup_exec(&c_list, &p_list, data, &env_list);
		c_list = c_list->next;
		data->index++;
		data->index_2++;
	}
	if (data->previous_fd > 0)
		close(data->previous_fd);
	if (data->fd_pipe[1] > 0)
		close(data->fd_pipe[1]);
	if (data->fd_pipe[0] > 0)
		close(data->fd_pipe[0]);
}

void	setup_exec(t_cmd **c_list, t_parsed **p_list, t_data *data,
		t_env **env_list)
{
	data->c = *c_list;
	data->p = *p_list;
	data->e = *env_list;
	data->previous_fd = data->fd_pipe[0];
	setup_fd(data, data->c);
	signal(SIGINT, SIG_IGN);
	data->pid[data->index] = fork();
	if (data->pid[data->index] == 0)
	{
		signal(SIGINT, signal_ctrl_c_in_child);
		if (data->c->is_ok && data->c->command)
		{
			redirections(data->c, data);
			if (data->c->command_int == COMMAND)
				get_path_and_exec(data->c, data->p, data, data->e);
			else
				go_to_builtin(*c_list, *p_list, data, env_list);
		}
		else
			skip_fork(c_list, p_list, data, env_list);
	}
	close_if(data);
}

void	redirections(t_cmd *list, t_data *data)
{
	if (data->pipe_count > 1 && data->index < data->pipe_count - 1)
		close(data->fd_pipe[0]);
	if (list->fd_in > 0 && dup2(list->fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (list->fd_out > 0 && (dup2(list->fd_out, STDOUT_FILENO) == -1))
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	go_to_builtin(t_cmd *c_temp, t_parsed *p_temp, t_data *data,
		t_env **env_list)
{
	exec_builtin(c_temp, p_temp, *env_list, data);
	free(data->pid);
	ft_free_all(data->c_list_adress, data->p_list_adress);
	ft_free_env(env_list);
	exit(data->error_status);
}

void	skip_fork(t_cmd **c_list, t_parsed **p_list, t_data *data,
		t_env **env_list)
{
	int	err_no;

	dprintf(2, "%s", "");
	err_no = (*c_list)->err_no;
	if (data->pipe_count > 1 && data->index < data->pipe_count - 1)
		close(data->fd_pipe[0]);
	if (data->previous_fd > 0)
		close(data->previous_fd);
	free(data->pid);
	ft_free_all(data->c_list_adress, p_list);
	ft_free_env(env_list);
	if (err_no == 1)
		exit(1);
	exit(data->error_status);
}
