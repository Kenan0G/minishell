/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exec_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:22:01 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/23 18:37:54 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_open(t_parsed *p_list, t_cmd *c_list, t_data *data)
{
	if (data->i == 0 && p_list->status == FILE_IN)
		fd_file_in(p_list, c_list, data);
	else if (data->i == 0 && p_list->status == HERE_DOC)
		fd_here_doc(c_list, data);
	else if (data->i == 0 && p_list->status == REDIR_OUT)
		fd_file_out(p_list, c_list, data);
	else if (data->i == 0 && p_list->status == APPEND)
		fd_append(p_list, c_list, data);
}

void	fd_file_in(t_parsed *p_list, t_cmd *c_list, t_data *data)
{
	if (c_list->fd_in > 0)
		close(c_list->fd_in);
	c_list->fd_in = open(p_list->token, O_RDONLY);
	if (c_list->fd_in == -1)
	{
		perror(p_list->token);
		c_list->is_ok = 0;
		data->i = 1;
	}
}

void	fd_here_doc(t_cmd *c_list, t_data *data)
{
	if (c_list->fd_in > 0)
		close(c_list->fd_in);
	c_list->fd_in = c_list->hd_fd[data->j];
	data->j++;
}

void	fd_append(t_parsed *p_list, t_cmd *c_list, t_data *data)
{
	if (c_list->fd_out > 0)
		close(c_list->fd_out);
	c_list->fd_out = open(p_list->next->token, O_WRONLY
			| O_APPEND | O_CREAT, 0777);
	if (c_list->fd_out == -1)
	{
		perror(p_list->next->token);
		c_list->is_ok = 0;
		data->i = 1;
	}
}

void	fd_file_out(t_parsed *p_list, t_cmd *c_list, t_data *data)
{
	if (c_list->fd_out > 0)
		close(c_list->fd_out);
	c_list->fd_out = open(p_list->next->token, O_WRONLY
			| O_TRUNC | O_CREAT, 0777);
	if (c_list->fd_out == -1)
	{
		perror(p_list->next->token);
		c_list->is_ok = 0;
		data->i = 1;
	}
}
