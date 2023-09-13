/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:49:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/13 14:21:47 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	execution(t_cmd *list, t_parsed *p_list, t_data *data, t_env **env_list)
{
	data->pid = malloc(sizeof(pid_t) * data->pipe_count);
	if (!data->pid)
		return (0);
	data->fd_pipe[0] = 0;
	data->fd_pipe[1] = 0;
	if (data->cmd_count == 1 && list->command_int == EXPORT)
		*env_list = exec_export(list, *env_list);
	else if (data->cmd_count == 1 && list->command_int == UNSET)
		*env_list = exec_unset(list, env_list);
	else if (data->cmd_count == 1 && list->command_int == CD)
		*env_list = exec_cd(list, *env_list, data);
	else if (data->cmd_count == 1 && list->command_int == EXIT)
		exec_exit(list, p_list, data, *env_list);
	else if (data->cmd_count > 0 && data->dont_loop != 1)
		execution_loop(list, p_list, data, *env_list);
	return (0);
}

void	exec_builtin(t_cmd *c_list, t_parsed *p_list, t_env *env_list,
		t_data *data)
{
	(void)p_list;
	if (c_list->command_int == ECHO)
		exec_echo(c_list);
	else if (c_list->command_int == PWD)
		exec_pwd(c_list);
	else if (c_list->command_int == EXIT)
		exec_exit(c_list, p_list, data, env_list);
	else if (c_list->command_int == ENV)
		exec_env(env_list, c_list);
	else if (c_list->command_int == EXPORT)
		env_list = exec_export(c_list, env_list);
	else if (c_list->command_int == UNSET)
		env_list = exec_unset(c_list, &env_list);
	else if (c_list->command_int == CD)
		exec_cd(c_list, env_list, data);
}

void	get_path_and_exec(t_cmd *list, t_parsed *p_list, t_data *data,
		t_env *env_list)
{
	char	**env;
	int		path;

	ft_path(env_char(env_list), data);
	path = is_path(list->command);
	if (path == 1)
		data->path = ft_strdup(list->command);
	else if (path == 0)
		data->path = path_check(data, list);
	else if (path == 2)
		data->path = NULL;
	if (data->path == NULL)
		error(data, p_list, env_list);
	env = env_char(env_list);
	if (execve(data->path, list->arg, env) == -1)
	{
		if (env)
			ft_free_map(env);
		clear_fork(list, p_list, data, env_list);
	}
}

void	error(t_data *data, t_parsed *p_list, t_env *env_list)
{
	free(data->pid);
	if (data->path_begining)
		ft_free_map(data->path_begining);
	ft_free_all(data->c_list_adress, &p_list);
	ft_free_env(&env_list);
	close(data->fd_pipe[0]);
	close(data->fd_pipe[1]);
	exit(127);
}

void	clear_fork(t_cmd *list, t_parsed *p_list, t_data *data, t_env *env_list)
{
	perror(list->arg[0]);
	ft_free_all(data->c_list_adress, &p_list);
	if (data->path_begining)
		ft_free_map(data->path_begining);
	if (data->pid)
		free(data->pid);
	if (data->path)
		free(data->path);
	if (env_list)
		ft_free_env(&env_list);
	close(data->fd_pipe[0]);
	close(data->fd_pipe[1]);
	exit(EXIT_FAILURE);
}
