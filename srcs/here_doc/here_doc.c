/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:50:45 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/11 15:13:44 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
				perror(c_list->hd_file[i]);
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
	pid_t		pid;
	int			exit_no;

	var = starthd();
	exit_no = 0;
	var->limiter = ft_strdup(c_list->limiter[i]);
	var->path = c_list->hd_file[i];
	var->fd = open_here_doc(var->path);
	pid = fork();
	if (pid == 0)
	{
		ft_free_all(&c_list, &p_list);
		ft_free_env(&data->envp);
		exit_no = readline_in_here_doc(data, var);
		free(var->line);
		free(var->limiter);
		close(var->fd);
		exit (exit_no);
	}
	waitpid(pid, &data->here_doc_exit, 0);
	if (WIFEXITED(data->here_doc_exit))
		data->here_doc_exit = WEXITSTATUS(data->here_doc_exit);
	return (return_here_doc(data, var));
}

int	readline_in_here_doc(t_data *data, t_here_doc *var)
{
	(void)data;
	while (g_in_here_doc == 1)
	{
		signal(SIGINT, signal_ctrl_c_here_doc);
		var->line = readline("> ");
		if (!var->line)
		{
			write(2, "warning: here-document delimited by end-of-file.\n",
				49);
			return (1);
		}
		if (!ft_strcmp(var->line, var->limiter))
			return (0);
		ft_putendl_fd(var->line, var->fd);
		signal(SIGINT, signal_ctrl_c_here_doc);
	}
	return (0);
}

int	return_here_doc(t_data *data, t_here_doc *var)
{
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
