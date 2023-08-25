/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:49:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/25 18:08:30 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execution(t_cmd *list, t_parsed *p_list, t_data *data, t_env **env_list)
{
	data->pid = malloc(sizeof(pid_t) * data->cmd_count);
	data->fd_pipe[0] = 0;
	data->fd_pipe[1] = 0;
	if (data->cmd_count == 1 && list->command_int == EXPORT)
		*env_list = exec_export(list, *env_list);
	else if (data->cmd_count == 1 && list->command_int == UNSET)
		*env_list = exec_unset(list, env_list);
	else if (data->cmd_count == 1 && list->command_int == CD)
		*env_list = exec_cd(list, *env_list, data);
	else if (data->cmd_count > 0)
		execution_loop(list, p_list, data, *env_list);
	// if (data->pid)
	// 	free(data->pid);
	return (0);
}

void	exec_builtin(t_cmd *c_list, t_parsed *p_list, t_env *env_list, t_data *data)
{
	if (c_list->command_int == ECHO)
		exec_echo(c_list);
	else if (c_list->command_int == PWD)
		exec_pwd(c_list);
	else if (c_list->command_int == EXIT)
		exec_exit(c_list, p_list);
	else if (c_list->command_int == ENV)
		exec_env(env_list, c_list);
	else if (c_list->command_int == EXPORT)
		env_list = exec_export(c_list, env_list);
	else if (c_list->command_int == UNSET)
		env_list = exec_unset(c_list, &env_list);
	else if (c_list->command_int == CD)
		exec_cd(c_list, env_list, data);
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
	char	**env;

	ft_path(env_char(env_list), data);
	if (is_path(list->command) == 1)
		data->path = list->command;
	else
		data->path = path_check(data, list);
	if (data->path == NULL)
	{
		free(data->pid);
		if (data->path_begining)
			ft_free_map(data->path_begining);
		ft_free_all(data->c_list_temp, &p_list, data, &env_list);
		ft_free_env(&env_list);
		close (data->fd_pipe[0]);
		close (data->fd_pipe[1]);
		exit (127);
	}
	env = env_char(env_list);
	if (execve(data->path, list->arg, env) == -1)
	{
		perror(list->arg[0]);
		ft_free_all(data->c_list_temp, &p_list, data, &env_list);
		ft_free_map(data->path_begining);
		free(data->pid);
		ft_free_env(&env_list);
		ft_free_map(env);
		close (data->fd_pipe[0]);
		close (data->fd_pipe[1]);
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


