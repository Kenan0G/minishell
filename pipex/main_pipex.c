/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:12:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/23 18:35:23 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"


/*
int	main(int ac, char **av, char **envp)
{
	t_data		data;
	int			is_here_doc;

	if (!av[1])
		return (ft_putstr_fd("Error\narguments\n", 2), 0);
	if (ft_strncmp("here_doc", av[1], 9) == 0)
		is_here_doc = 1;
	else
		is_here_doc = 0;
	if ((is_here_doc == 0 && ac < 5) || (is_here_doc == 1 && ac < 6))
		return (ft_putstr_fd("Error\narguments\n", 2), 0);
	data_init(&data, ac, av, is_here_doc);
	ft_loop(&data, envp);
	ft_close(&data);
	ft_wait(&data, ac);
	unlink(".hd_file");
	return (0);
}




void	data_init(t_data *data, int ac, char **av, int is_here_doc)
{
	ft_memset(data, 0, sizeof(t_data));
	data->ac = ac;
	data->av = av;
	data->index = 0;
	data->here_doc = is_here_doc;
	data->nb_cmd = ac - 3 - data->here_doc;
	data->pid = malloc(sizeof(pid_t) * (data->nb_cmd));
	if (is_here_doc == 1)
		here_doc(data->av[2], data);
}

void	ft_loop(t_data *data, char **envp)
{
	while (data->index < data->nb_cmd)
	{
		data->fd_temp = data->fd_pipe[0];
		if (data->index + 1 < data->nb_cmd)
		{
			if (pipe(data->fd_pipe) == -1)
				return (perror("Pipe"));
		}
		else
			close(data->fd_pipe[1]);
		data->pid[data->index] = fork();
		if (data->pid[data->index] == 0)
			exec(data, envp);
		if (data->fd_temp > 0)
			close(data->fd_temp);
		if (data->fd_pipe[1] > 0)
			close(data->fd_pipe[1]);
		data->index++;
	}
}

void	ft_free_map(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

void	ft_error(t_data *data, int error)
{
	(void)error;
	if (data->path_begining)
		ft_free_map(data->path_begining);
	if (data->cmd)
		ft_free_map(data->cmd);
	if (data->pid)
		free(data->pid);
	if (data->path)
		free (data->path);
	ft_close(data);
	exit (EXIT_FAILURE);
}
*/