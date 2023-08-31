/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:50:45 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/31 20:16:49 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	in_here_doc= 0;

int	hd_execution(t_parsed *p_list, t_cmd *cmd_list)
{
	int		i;
	t_cmd	*c_list;

	(void)p_list;
	c_list = cmd_list;
	signal(SIGINT, signal_ctrl_c);
	while (c_list)
	{
		i = 0;
		while (i < c_list->nb_here_doc && in_here_doc == 1)
		{
			generate_hd_file_name(c_list, i);
			unlink(c_list->hd_file[i]);
			c_list->hd_fd[i] = here_doc(c_list->limiter[i], c_list->hd_file[i]);
			if (in_here_doc == 0)
				return (0);
			c_list->hd_fd[i] = open(c_list->hd_file[i], O_RDWR, 0644);
			if (c_list->hd_fd[i] <= 0)
			{
				perror(c_list->hd_file[i]);
			}
			i++;
		}
		if (in_here_doc == 0)
			return (0);
		c_list->hd_file[i] = NULL;
		c_list = c_list->next;
	}
	signal(SIGINT, signal_ctrl_c);
	return (1);
}

void	generate_hd_file_name(t_cmd *c_list, int i)
{
	char	*file_no;
	char	*file_temp_name;

	file_no = ft_itoa(i + 1);
	file_temp_name = ft_strjoin(".here_doc_", file_no);
	c_list->hd_file[i] = ft_strjoin(file_temp_name, ".tmp");
	free(file_no);
	free(file_temp_name);
}

int	here_doc(char *limiter, char *path)
{
	char	*line;
	int		fd;
	// int		x;

	// x = dup(0);
	fd = open_here_doc(path);
	while (in_here_doc == 1)
	{
		line = readline("> ");
		// printf("line = %s\n", line);
		if (!line)
		{
			write(2, "warning: here-document delimited by end-of-file.\n", 49);
			break ;
		}
		if (in_here_doc == 0)
		{
			// close(x);
			break ;
		}
		if (!ft_strcmp(line, limiter))
			break ;
		if (line)
			ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	if (in_here_doc == 0)
		return (printf("return test\n"), 0);
	if (line)
		free(line);
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

// void	exit_here_doc(int signo)
// {
//     if (signo == SIGINT) 
// 	{
// 		ft_putstr_fd("^C\n", 1);
// 		exit (0);
// 	}
// }