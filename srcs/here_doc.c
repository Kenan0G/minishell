/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:50:45 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/14 15:53:37 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	here_doc(char *limiter, char *path)
{
	char	*line;
	int		fd;

	fd = open_here_doc(path);
	while (1)
	{
		write(1, "> ", 1);
		line = get_next_line(1, 0);
		if ((ft_strlen(line) - 1 == ft_strlen(limiter))
			&& ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
				break ;
		if (line)
		{
			dprintf(2, "=========== line = [%s]\n", line);
			ft_putstr_fd(line, fd);
		}
		free(line);
	}
	// get_next_line(1, 1);
	if (line)
		free(line);
	close(fd);
	return (fd);
}
// les deux fichiers tmp s'ouvrent en meme temps

int	open_here_doc(char *path)
{
	int		fd;

	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		// unlink(path);
		// fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
		// if (fd == -1)
		// {
			// close(data->fd_pipe[1]);
			perror(path);
			exit (EXIT_FAILURE);
			// free(data->pid);
			// exit (EXIT_FAILURE);
		// }
	}
	// if (path)
	// 	free(path);
	return (fd);
}
