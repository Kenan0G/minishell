/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:49:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/14 17:22:21 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_pipe(t_cmd *list, t_data *data)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->is_ok)
		{
			data->previous_fd = data->fd_pipe[0];
			if (list->next)
			{
				if (pipe(data->fd_pipe) == -1)
					return (perror("Pipe"));
				if (list->fd_in == 0)
					list->fd_in = data->previous_fd;
				if (list->fd_out == 0)
					list->fd_out = data->fd_pipe[1];
			}
			else
			{
				if (list->fd_in == 0)
					list->fd_in = data->previous_fd;
				if (i > 0)
					close(data->fd_pipe[1]);
			}
			data->pid[data->index] = fork();
			if (data->pid[data->index] == 0)
			{

				redirections(list, data);
				get_path_and_exec(list, data);
			}
			if (data->previous_fd > 0)
				close(data->previous_fd);
			if (data->fd_pipe[1] > 0)
				close (data->fd_pipe[1]);
			list = list->next;
			data->index++;
			i++;
		}
		else
		{
			list = list->next;
			data->index++;
			i++;
		}
	}
}

void	redirections(t_cmd *list, t_data *data)
{
	if (data->cmd_count > 1 && data->index < data->cmd_count - 1)
		close(data->fd_pipe[0]);
	if (list->fd_in > 0 && dup2(list->fd_in, STDIN_FILENO) == -1)
	{
		perror("Error fd_in");
		// free
		exit(EXIT_FAILURE); // recuperer le bon code erreur
	}
	if (list->fd_out > 0 && (dup2(list->fd_out, STDOUT_FILENO) == -1))
	{
		perror("Error fd_out");
		// free
		exit(EXIT_FAILURE); // recuperer le bon code erreur
	}
}

void	get_path_and_exec(t_cmd *list, t_data *data)
{
	ft_path(data->env, data);
	if (is_path(list->command) == 1)
		data->path = list->command;
	else
		data->path = path_check(data, list);
	// dprintf(2, "\ndata->path = %s\n", data->path);
	// int i = 0;
	// while (list->arg[i])
	// {
	// 	dprintf(2, "list->arg[%d] = %s\n", i, list->arg[i]);
	// 	i++;
	// }
	// dprintf(2, "\n");
	if (execve(data->path, list->arg, data->env) == -1)
	{
		perror("execve");
		exit (EXIT_FAILURE);
	}
}

int	main_exec(t_cmd *list, t_data *data)
{
	// print_cmd_list(list);
	data->pid = malloc(sizeof(pid_t) * data->cmd_count);
	data->index = 0;
	data->fd_pipe[0] = 0;
	data->fd_pipe[1] = 0;
	exec_pipe(list, data);
	ft_wait(data);
	return (0);
}

int main (int ac, char **av, char **env)
{
	t_cmd			*cmd_list;
	t_temp			*token;
	t_data			data;

	(void)ac;
	init_data(&data, env);
	token = temp_list(&data, av, av[1]);
	cmd_list = create_cmd_list(token, &data);
	// (void)cmd_list;
	// print_list(token);
	main_exec(cmd_list, &data);
	ft_unlink(cmd_list);
	return (0);
}



void	ft_wait(t_data *data)
{
	while (data->index-- > 0)
		waitpid(data->pid[data->index], NULL, 0);
	free(data->pid);
}

void	ft_unlink(t_cmd *list)
{
	t_cmd	*temp;
	int		i;

	temp = list;
	while (temp)
	{
		i = 0;
		while (temp->here_doc_tmp[i])
		{
			unlink (temp->here_doc_tmp[i]);
			free (temp->here_doc_tmp[i]);
			free (temp->limiter[i]);
			i++;
		}
		free(temp->here_doc_tmp);
		free (temp->limiter);
		temp = temp->next;
	}
}

void	ft_free_list(t_cmd **lst)
{
	t_cmd	*temp;
	t_cmd	*tmp2;

	temp = (*lst);
	while (temp)
	{
		tmp2 = temp->next;
		free(temp);
		temp = tmp2;
	}
}


//-------------------------------------------------------------------------

	// afficher les arguments et le path juste avant le execve
	
	// dprintf(2, "\ndata->path = %s\n", data->path);
	// int i = 0;
	// while (list->arg[i])
	// {
	// 	dprintf(2, "list->arg[%d] = %s\n\n", i, list->arg[i]);
	// 	i++;
	// }

//-------------------------------------------------------------------------
	
	// afficher les fd

	// dprintf(2, "[%d]--fd_in 		= %d\n", i, list->fd_in);
	// dprintf(2, "[%d]--fd_out		= %d\n", i, list->fd_out);
	// dprintf(2, "[%d]--fd_pipe[1]	= %d\n", i, data->fd_pipe[1]);
	// dprintf(2, "[%d]--fd_pipe[0]	= %d\n", i, data->fd_pipe[0]);
	// dprintf(2, "[%d]--previous fd	= %d\n", i, data->previous_fd);

//-------------------------------------------------------------------------

	// fonction norm get value
	
	// t_temp	*get_value_i_j(t_temp *p_list, int *i, int *j)
	// {
	// 		while (p_list && p_list->status != PIPE)
	// 		{
	// 		if (p_list->status == ARG || p_list->status == COMMAND)
	// 			i++;
	// 		else if (p_list->status == HERE_DOC)
	// 			j++;
	// 		p_list = p_list->next;
	// 		}
	// 		return (p_list);
	// }

//-------------------------------------------------------------------------
