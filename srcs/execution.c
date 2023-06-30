/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:49:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/30 13:29:16 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execution(t_cmd *list, t_parsed *p_list, t_data *data)
{
	// printf("data->cmd_count = %d\n", data->cmd_count);
	data->pid = malloc(sizeof(pid_t) * data->cmd_count);
	data->index = 0;
	data->fd_pipe[0] = 0;
	data->fd_pipe[1] = 0;
	execution_loop(list, p_list, data);
	return (0);
}

void	exec_echo(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	// (void)p_list;
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (c_list->arg[i])
	{
		if (i == 1 && !ft_strcmp(c_list->arg[1], "-n"))
			newline = 0;
		else
		{
			printf("%s", c_list->arg[i]);
			if (c_list->arg[i + 1])
				printf(" ");
		}
		i++;
	}
	if (newline)
		printf("\n");
	free(data->pid);
	ft_free_all(&c_list, &p_list, data);
	exit (0);
	// kill(data->pid[data->index], SIGTERM);
}

void	exec_cd(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	(void)p_list;
	(void)c_list;
	(void)data;
	printf("exec_cd\n");
	free(data->pid);
	ft_free_all(&c_list, &p_list, data);
	exit (0);
}

void	exec_pwd(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	char	*buf;
	char	*str;

	buf = NULL;
	str = getcwd(buf, 0);
	printf("%s\n", str);
	free(data->pid);
	ft_free_all(&c_list, &p_list, data);
	exit (0);
}

void	exec_export(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	(void)p_list;
	t_env	*temp;
	int		i;
	// int		lenght;

	i = 1;
	// lenght = 0;
	while (c_list->arg[i])
	{
		temp = data->envp;
		// while (c_list->arg[i][lenght] && c_list->arg[i][lenght] != '=')
		// 	lenght++;
		// printf("legnht = %d , %c\n\n", lenght, c_list->arg[i][lenght]);
		// while (temp)
		// {
		// 	if (!ft_strncmp(temp->env, c_list->arg[i], lenght))
		// 	{
		// 		if (temp->env)
		// 			free (temp->env);
		// 		temp->env = malloc(sizeof(char) * ft_strlen(c_list->arg[i]) + 1);
		// 		temp->env = c_list->arg[i];
		// 	}
		// 	temp = temp->next;
		// }
		if (temp == NULL)
			my_lstadd_back_env(&(data->envp), my_lstnew_env(c_list->arg[i]));
		i++;
	}
	print_env(data->envp);
	// free(data->pid);
	// ft_free_all(&c_list, &p_list, data);
	// exit (0);
}

void	exec_unset(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	(void)p_list;
	(void)c_list;
	(void)data;
	printf("exec_unset\n");
	free(data->pid);
	ft_free_all(&c_list, &p_list, data);
	exit (0);
}

void	exec_env(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	(void)p_list;
	(void)c_list;
	// get_env(data);
	print_env(data->envp);
	free(data->pid);
	ft_free_all(&c_list, &p_list, data);
	exit (0);
}

void	exec_exit(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	(void)p_list;
	(void)c_list;
	(void)data;
	printf("exec_exit\n");
	free(data->pid);
	ft_free_all(&c_list, &p_list, data);
	exit (0);
}

void	exec_builtin(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	if (c_list->command_int == ECHO)
		exec_echo(c_list, p_list, data);
	else if (c_list->command_int == PWD)
		exec_pwd(c_list, p_list, data);
	else if (c_list->command_int == EXIT)
		exec_exit(c_list, p_list, data);
	else if (c_list->command_int == ENV)
		exec_env(c_list, p_list, data);
	// else if (c_list->command_int == CD)
	// 	exec_cd(c_list, p_list, data);
	// else if (c_list->command_int == UNSET)
	// 	exec_unset(c_list, p_list, data);
	// else if (c_list->command_int == EXPORT)
	// 	exec_export(c_list, p_list, data);
}

void	execution_loop(t_cmd *list, t_parsed *p_list, t_data *data)
{
	int		i;
	t_cmd	*c_list;

	i = 0;
	c_list = list;
	while (c_list)
	{
		if (c_list->is_ok)
		{
			data->previous_fd = data->fd_pipe[0];
			if (c_list->next)
			{
				if (pipe(data->fd_pipe) == -1)
					return (perror("Pipe"));
				if (c_list->fd_in == 0)
					c_list->fd_in = data->previous_fd;
				if (c_list->fd_out == 0)
					c_list->fd_out = data->fd_pipe[1];
			}
			else
			{
				if (c_list->fd_in == 0)
					c_list->fd_in = data->previous_fd;
				if (i > 0)
					close(data->fd_pipe[1]);
			}
			if (data->cmd_count == 1 && (c_list->command_int == EXPORT))
			{
				exec_export(c_list, p_list, data);
				data->pid[data->index] = fork();
				if (data->pid[data->index] == 0)
				{
					free(data->pid);
					ft_free_all(&c_list, &p_list, data);
				}
				// print_env(data->envp);
			}
			else
			{
				data->pid[data->index] = fork();
				if (data->pid[data->index] == 0)
				{
					// print_env(data->envp);
					redirections(c_list, data);
					if (c_list->command_int == COMMAND)
						get_path_and_exec(c_list, p_list, data);
					else
						exec_builtin(c_list, p_list, data);
				}
				if (data->previous_fd > 0)
					close(data->previous_fd);
				if (data->fd_pipe[1] > 0)
					close (data->fd_pipe[1]);
				c_list = c_list->next;
				data->index++;
				i++;
			}
		}
		else
		{
			data->pid[data->index] = fork();
			if (data->pid[data->index] == 0)
			{
				ft_free_all(&list, &p_list, data);
				free(data->pid);
				exit(0);
			}
			c_list = c_list->next;
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

void	get_path_and_exec(t_cmd *list, t_parsed *p_list, t_data *data)
{
	(void)p_list;
	ft_path(data->env, data);
	if (is_path(list->command) == 1)
		data->path = list->command;
	else
		data->path = path_check(data, list);
	if (data->path == NULL)
	{
		free(data->pid);
		ft_free_map(data->path_begining);
		ft_free_all(&list, &p_list, data);
		exit (0);
	}
	else if (execve(data->path, list->arg, data->env) == -1)
	{
		// perror("execve");
		// ft_free_all(&list, &p_list, data);

		exit (EXIT_FAILURE);
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


