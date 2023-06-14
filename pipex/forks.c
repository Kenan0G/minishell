/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:43:59 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/14 15:23:21 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"


/*
void	exec(t_data *data, char **envp)
{
	if (data->index == 0)
		ft_first_cmd(data);
	else if (data->index != data->nb_cmd - 1)
		ft_middle_cmd(data);
	else
		ft_last_cmd(data);
	get_path(envp, data);
	if (execve(data->path, data->cmd, envp) == -1)
	{
		ft_error_path(data, NULL);
		if (data->cmd)
			ft_free_map(data->cmd);
		if (data->pid)
			free(data->pid);
		if (data->path)
			free(data->path);
		exit(EXIT_FAILURE);
	}
}

void	ft_first_cmd(t_data *data)
{
	close(data->fd_pipe[0]);
	open_infile(data);
	if (dup2(data->fd_infile, STDIN_FILENO) == -1)
	{
		perror("Error");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->fd_pipe[1], STDOUT_FILENO) == -1)
	{
		perror("Error");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
}

void	ft_middle_cmd(t_data *data)
{
	close(data->fd_pipe[0]);
	if (dup2(data->fd_temp, STDIN_FILENO) == -1)
	{
		perror("Error");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->fd_pipe[1], STDOUT_FILENO) == -1)
	{
		perror("Error");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
}

void	ft_last_cmd(t_data *data)
{
	data->fd_outfile = open(data->av[data->ac - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->fd_outfile == -1)
	{
		close(data->fd_pipe[0]);
		perror("Error");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->fd_temp, STDIN_FILENO) == -1)
	{
		perror("Error");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
	{
		perror("Error");
		free(data->pid);
		exit(EXIT_FAILURE);
	}
}

void	open_infile(t_data *data)
{
	if (data->here_doc == 0)
		data->fd_infile = open(data->av[1], O_RDONLY);
	else
		data->fd_infile = open(".here_doc_tmp", O_RDONLY);
	if (data->fd_infile == -1)
	{
		close(data->fd_pipe[1]);
		perror(data->av[1]);
		free(data->pid);
		exit(EXIT_FAILURE);
	}
}

*/