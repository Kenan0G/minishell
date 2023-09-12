/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:24:48 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 14:34:53 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	setup_fd(t_data *data, t_cmd *c_temp)
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

void	close_if(t_data *data)
{
	if (data->previous_fd > 0)
		close(data->previous_fd);
	if (data->fd_pipe[1] > 0)
		close(data->fd_pipe[1]);
}
