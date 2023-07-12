/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:49:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/07/12 14:25:00 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execution(t_cmd *list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	// printf("data->cmd_count = %d\n", data->cmd_count);
	data->pid = malloc(sizeof(pid_t) * data->cmd_count);
	data->index = 0;
	data->fd_pipe[0] = 0;
	data->fd_pipe[1] = 0;
	if (data->cmd_count == 1 && list->command_int == EXPORT)
		env_list = exec_export(list, p_list, data, env_list);
	else if (data->cmd_count == 1 && list->command_int == UNSET)
		env_list = exec_unset(list, p_list, data, &env_list);
	else
		execution_loop(list, p_list, data, env_list);
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
	ft_free_all(&c_list, &p_list, data, NULL);
	// exit (0);
	// kill(data->pid[data->index], SIGTERM);
}

void	exec_cd(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	(void)p_list;
	(void)c_list;
	(void)data;
	printf("exec_cd\n");
	free(data->pid);
	ft_free_all(&c_list, &p_list, data, NULL);
	// exit (0);
}

void	exec_pwd(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	char	*buf;
	char	*str;

	buf = NULL;
	str = getcwd(buf, 0);
	printf("%s\n", str);
	free(data->pid);
	ft_free_all(&c_list, &p_list, data, NULL);
	// exit (0);
}

t_env	*exec_export(t_cmd *c_list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	(void)p_list;
	(void)data;
	t_env	*temp;
	int		i;
	int		lenght;
	int		check;

	i = 1;
	while (c_list->arg[i])
	{
		lenght = 0;
		check = 0;
		temp = env_list;
		while (c_list->arg[i][lenght] && c_list->arg[i][lenght] != '=')
			lenght++;
		if (!c_list->arg[i][lenght])
			return (env_list);
		while (temp)
		{
			if (!ft_strncmp(temp->env, c_list->arg[i], lenght))
			{
				if (temp->env)
					free (temp->env);
				temp->env = malloc(sizeof(char) * ft_strlen(c_list->arg[i]) + 1);
				ft_strlcpy(temp->env, c_list->arg[i], ft_strlen(c_list->arg[i]) + 1);
				check = 1;
			}
			temp = temp->next;
		}
		if (temp == NULL && check == 0)
			my_lstadd_back_env(&env_list, my_lstnew_env(c_list->arg[i]));
		i++;
	}
	return (env_list);
}

t_env *exec_unset(t_cmd *c_list, t_parsed *p_list, t_data *data, t_env **env_list)
{
	(void)p_list;
	(void)data;
	t_env *current;
	t_env *prev;
	t_env *temp;
	int i;

	i = 1;
	temp = NULL;
	while (c_list->arg[i])
	{
		current = *env_list;
		prev = NULL;
		while (current)
		{
			// printf("%s\n\n", current->env);
			if (!ft_strncmp(current->env, c_list->arg[i], ft_strlen(c_list->arg[i])))
			{
				if (prev)
					prev->next = current->next;
				else
				{	
					*env_list = current->next;
					prev = *env_list;
					// print_env(*env_list);
					// print_env(prev);
				}
				
				temp = current;
				current = current->next;
				free(temp);
				temp = NULL;
			}
			else
			{
				prev = current;
				current = current->next;
			}
		}
		i++;
	}

	print_env(*env_list);
	return (*env_list);
}

void	exec_env(t_cmd *c_list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	(void)p_list;
	(void)c_list;
	// get_env(data);
	print_env(env_list);
	free(data->pid);
	ft_free_all(&c_list, &p_list, data, &env_list);
	// exit (0);
}

void	exec_exit(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	(void)p_list;
	(void)c_list;
	(void)data;
	printf("exec_exit\n");
	free(data->pid);
	ft_free_all(&c_list, &p_list, data, NULL);
	// exit (0);
}

void	exec_builtin(t_cmd *c_list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	if (c_list->command_int == ECHO)
		exec_echo(c_list, p_list, data);
	else if (c_list->command_int == PWD)
		exec_pwd(c_list, p_list, data);
	else if (c_list->command_int == EXIT)
		exec_exit(c_list, p_list, data);
	else if (c_list->command_int == ENV)
		exec_env(c_list, p_list, data, env_list);
	else if (c_list->command_int == EXPORT)
		env_list = exec_export(c_list, p_list, data, env_list);
	else if (c_list->command_int == UNSET)
		env_list = exec_unset(c_list, p_list, data, &env_list);
	// else if (c_list->command_int == CD)
	// 	exec_cd(c_list, p_list, data);
	exit(0);
}

void	execution_loop(t_cmd *list, t_parsed *p_list, t_data *data, t_env *env_list)
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
					data->pid[data->index] = fork();
					if (data->pid[data->index] == 0)
					{
						// print_env(data->envp);
						if (c_list->command_int != EXPORT)
							redirections(c_list, data);
						if (c_list->command_int == COMMAND)
							get_path_and_exec(c_list, p_list, data, env_list);
						else
							exec_builtin(c_list, p_list, data, env_list);
					}
					if (data->previous_fd > 0)
						close(data->previous_fd);
					if (data->fd_pipe[1] > 0)
						close (data->fd_pipe[1]);
					c_list = c_list->next;
					data->index++;
					i++;
				// }
			}
			else
			{
				data->previous_fd = 0;
				// dprintf(2, "test isok = 0 \n\n");
				data->pid[data->index] = fork();
				if (data->pid[data->index] == 0)
				{
					ft_free_all(&list, &p_list, data, &env_list);
					free(data->pid);
					exit(0);
				}
				// dprintf(2, "test after \n\n");
				c_list = c_list->next;
				data->index++;
				// i++;
			}
		}
	// }
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

void	get_path_and_exec(t_cmd *list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	(void)p_list;
	ft_path(env_execve(env_list), data);
	if (is_path(list->command) == 1)
		data->path = list->command;
	else
		data->path = path_check(data, list);
	if (data->path == NULL)
	{
		free(data->pid);
		ft_free_map(data->path_begining);
		ft_free_all(&list, &p_list, data, &env_list);
		exit (0);
	}
	else if (execve(data->path, list->arg, env_execve(env_list)) == -1)
	{
		printf("test\n\n");
		// perror("execve");
		// ft_free_all(&list, &p_list, data);

		exit (EXIT_FAILURE);
	}
}

char	**env_execve(t_env *env_list)
{
	t_env	*temp;
	char	**env;
	int		i;

	i = 0;
	temp = env_list;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	temp = env_list;
	while (temp)
	{
		env[i] = temp->env;
		temp = temp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
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


