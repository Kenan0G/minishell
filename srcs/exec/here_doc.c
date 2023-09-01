/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:50:45 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/01 19:02:49 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	in_here_doc= 0;

int	hd_execution(t_parsed *p_list, t_cmd *cmd_list, t_data *data)
{
	int		i;
	t_cmd	*c_list;
	pid_t	pid;
	int		exit_no;

	(void)p_list;
	c_list = cmd_list;
	data->exit_here_doc = 0;
	signal(SIGINT, signal_ctrl_c);
	while (c_list)
	{
		i = 0;
		while (i < c_list->nb_here_doc && in_here_doc == 1)
		{
			generate_hd_file_name(c_list, i);
			unlink(c_list->hd_file[i]);
			// pid = fork();
			// if (pid == 0)
			// {
				// data->exit_here_doc = here_doc(c_list, p_list, data, i);
			// 	ft_free_all(&c_list, &p_list, data, &data->envp);
			// 	ft_free_env(&data->envp);
			// 	if (data->exit_here_doc >= 0)
			// 		exit (data->exit_here_doc);
			// 	else
			// 	{
			// 		ft_close(c_list, i);
			// 		exit (-1);
			// 	}	
			// }
			// waitpid(pid, &exit_no, 0);
			// if (in_here_doc == 0)
			// 	return (0);
			// if (WIFEXITED(exit_no))
			// 	exit_no = WEXITSTATUS(exit_no);
			// c_list->hd_fd[i] = exit_no;
			c_list->hd_fd[i] = here_doc(c_list, p_list, data, i);
			c_list->hd_fd[i] = open(c_list->hd_file[i], O_RDWR, 0644);
			if (c_list->hd_fd[i] <= 0)
			{
				perror(c_list->hd_file[i]);
			}
			i++;
		}
		if (in_here_doc == 0)
		{
			return (0);
		}
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

int	here_doc(t_cmd *c_list, t_parsed *p_list, t_data *data, int i)
{
	(void)p_list;
	(void)data;
	t_here_doc	var;
// 
// 
// essayer avec un pid seulement sur le readline dans la boucle
// et gerer les variables end essous
// 
	var->limiter = c_list->limiter[i];
	var->path = c_list->hd_file[i];
	var->fd = open_here_doc(var->path);
	while (in_here_doc == 1)
	{
		if (in_here_doc == 0)
			return (-1);
		line = readline("> ");
		// printf("line = %s\n", line);
		if (!line)
		{
			write(2, "warning: here-document delimited by end-of-file.\n", 49);
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
		return (-1);
	if (line)
		free(line);
	return (fd);
}

void	ft_close(t_cmd *c_list, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (c_list->hd_fd[j] > 0)
			close(c_list->hd_fd[j]);
		j++;
	}
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