/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:50:45 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/05 17:51:37 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	in_here_doc= 0;

int	hd_execution(t_parsed *p_list, t_cmd *cmd_list, t_data *data)
{
	int		i;
	t_cmd	*c_list;
	// pid_t	pid;
	// int		exit_no;

	(void)p_list;
	c_list = cmd_list;
	data->exit_here_doc = 0;
	while (c_list)
	{
		i = 0;
		data->here_doc_exit = 0;
		while (i < c_list->nb_here_doc && in_here_doc == 1)
		{
			generate_hd_file_name(c_list, i);
			unlink(c_list->hd_file[i]);
			c_list->hd_fd[i] = here_doc(c_list, p_list, data, i);
			if (data->here_doc_exit == -1)
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
	pid_t	pid;
	// int		exit_no;
// 
// 
// essayer avec un pid seulement sur le readline dans la boucle
// et gerer les variables end essous
// 
	// pid = NULL;
	ft_memset(&var, 0, sizeof(t_here_doc));
	var.limiter = ft_strdup(c_list->limiter[i]);
	var.path = c_list->hd_file[i];
	var.fd = open_here_doc(var.path);
	// data->here_doc_exit = 0;
	while (data->here_doc_exit == 0 && in_here_doc == 1)
	{
		dprintf(2, "entree dans la boucle\n\n");
		dprintf(2, "%d\n\n", data->here_doc_exit);
		// in_here_doc = 1;
		pid = fork();
		if (pid == 0)
		{
			dprintf(2, "entree dans un pipe\n\n");
			signal(SIGINT, signal_ctrl_c_here_doc);
			printf("in_here_doc = %d\n", in_here_doc);
			ft_free_all(&c_list, &p_list, data, NULL);
			ft_free_env(&data->envp);
			var.line = readline("> ");
			if (!var.line)
			{
				free(var.limiter);
				close(var.fd);
				write(2, "warning: here-document delimited by end-of-file.\n", 49);
				exit (1) ;
			}
			if (!ft_strcmp(var.line, var.limiter))
			{	
				free(var.limiter);
				close(var.fd);
				exit (1) ;
			}
			if (var.line)
				ft_putendl_fd(var.line, var.fd);
			free(var.line);
			free(var.limiter);
			close(var.fd);
			signal(SIGINT, signal_ctrl_c_here_doc);
			exit (0);
		}
		waitpid(pid, &data->here_doc_exit, 0);
		if (WIFEXITED(data->here_doc_exit))
			data->here_doc_exit = WEXITSTATUS(data->here_doc_exit);
		printf("data->here_doc_exit = %d\n", data->here_doc_exit);
	}
	close(var.fd);
	if (var.limiter)
		free(var.limiter);
	// if (var.line)
	// 	free(var.line);
	if (in_here_doc == 0)
		return (-1);
	return (var.fd);
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