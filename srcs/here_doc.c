/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:50:45 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/23 18:40:25 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hd_execution(t_temp *p_list, t_cmd *cmd_list)
{
	int		i;
	t_cmd	*c_list;

	(void)p_list;
	c_list = cmd_list;
	while (c_list)
	{
		i = 0;
		while (i < c_list->nb_here_doc)
		{
			c_list->hd_file[i] = ft_strjoin(ft_strjoin(".here_doc_",
						ft_itoa(i + 1)), ".tmp");
			unlink(c_list->hd_file[i]);
			c_list->hd_fd[i] = here_doc(c_list->limiter[i], c_list->hd_file[i]);
			c_list->hd_fd[i] = open(c_list->hd_file[i], O_RDWR, 0644);
			if (c_list->hd_fd[i] <= 0)
			{
				perror(c_list->hd_file[i]);
			}
			i++;
		}
		c_list->hd_file[i] = NULL;
		c_list = c_list->next;
	}
}

int	here_doc(char *limiter, char *path)
{
	char	*line;
	int		fd;

	fd = open_here_doc(path);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "warning: here-document delimited by end-of-file.\n", 49);
			break ;
		}
		if (!ft_strcmp(line, limiter))
			break ;
		if (line)
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	return (fd);
}

int	open_here_doc(char *path)
{
	int		fd;

	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(path);
		exit (EXIT_FAILURE);
	}
	return (fd);
}
