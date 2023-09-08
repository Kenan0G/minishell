/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:50:45 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/08 18:25:51 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	g_in_here_doc= 0;

int	hd_execution(t_parsed *p_list, t_cmd *cmd_list, t_data *data)
{
	int		i;
	t_cmd	*c_list;

	c_list = cmd_list;
	while (c_list)
	{
		i = 0;
		data->here_doc_exit = 0;
		while (i < c_list->nb_here_doc && g_in_here_doc == 1)
		{
			data->here_doc_exit = 0;
			generate_hd_file_name(c_list, i);
			unlink(c_list->hd_file[i]);
			c_list->hd_fd[i] = here_doc(c_list, p_list, data, i);
			if (data->here_doc_exit == 130)
				return (-1);
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
	return (1);
}

int	here_doc(t_cmd *c_list, t_parsed *p_list, t_data *data, int i)
{
	t_here_doc	*var;
	pid_t	pid;
	int		exit_no;

	var = starthd();
	exit_no = 0;
	var->limiter = ft_strdup(c_list->limiter[i]);
	var->path = c_list->hd_file[i];
	var->fd = open_here_doc(var->path);
	pid = fork();
	if (pid == 0)
	{
		ft_free_all(&c_list, &p_list, data, NULL);
		ft_free_env(&data->envp);
		while (data->here_doc_exit == 0 && g_in_here_doc == 1)
		{
			signal(SIGINT, signal_ctrl_c_here_doc);
			var->line = readline("> ");
			if (!var->line)
			{
				write(2, "warning: here-document delimited by end-of-file.\n", 49);
				exit_no = 1;
				break ;
			}
			if (!ft_strcmp(var->line, var->limiter))
			{	
				exit_no = 1;
				break ;
			}
			ft_putendl_fd(var->line, var->fd);
			signal(SIGINT, signal_ctrl_c_here_doc);
		}
		free(var->line);
		free(var->limiter);
		close(var->fd);
		exit (exit_no);
	}
	waitpid(pid, &data->here_doc_exit, 0);
	if (WIFEXITED(data->here_doc_exit))
		data->here_doc_exit = WEXITSTATUS(data->here_doc_exit);
	close(var->fd);
	if (var->limiter)
		free(var->limiter);
	if (var->line)
		free(var->line);
	if (data->here_doc_exit == 130)
		return (-1);
	else if (data->here_doc_exit == 1)
		return (0);
	return (var->fd);
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

void *starthd()
{
	static t_here_doc var = {0};
	return (&var);
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

			// dprintf(2, "entree dans la boucle\n\n");
			// dprintf(2, "%d\n\n", data->here_doc_exit);
			// g_in_here_doc = 1;
			// dprintf(2, "entree dans un pipe\n\n");
			// printf("g_in_here_doc = %d\n", g_in_here_doc);