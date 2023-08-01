/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:42:04 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/01 15:46:49 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_end(t_cmd **c_list, t_parsed **p_list, t_data *data, t_env **env_list)
{
	// (void)env_list;
	ft_wait(data);
	ft_unlink(*c_list);
	ft_free_all(c_list, p_list, data, env_list);
}

void	ft_free_all(t_cmd **c_list, t_parsed **p_list, t_data *data, t_env **env_list)
{
	(void)env_list;
	if (c_list)
		ft_free_cmd_list(c_list);
	if (p_list)
		ft_free_p_list(p_list, data);
	// if (env_list)
	// 	ft_free_env(env_list);
	if (data->str_split)
		free(data->str_split);
}

// void	ft_wait(t_data *data)
// {
// 	// int i = 0;
// 	while (data->index-- > 0)
// 	{
// 		// printf("index = %d\n", data->index);
// 		waitpid(data->pid[data->index], NULL, 0);
// 		// i++;
// 	}
// 	free(data->pid);
// }

void	ft_wait(t_data *data)
{
	int status;

	while (data->index-- > 0)
	{
		waitpid(data->pid[data->index], &status, 0);
		status = WEXITSTATUS(status);
		printf("status = %d\n", status);
	}
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
		while (temp->hd_file[i])
		{
			unlink (temp->hd_file[i]);
			i++;
		}
		temp = temp->next;
	}
}

void	ft_free_cmd_list(t_cmd **lst)
{
	t_cmd	*temp;
	t_cmd	*tmp2;
	int		i;
	
	temp = (*lst);
	while (temp)
	{
		i = 0;
		if (temp->fd_in > 0)
			close(temp->fd_in);
		if (temp->fd_out > 0)
			close(temp->fd_out);
		while (i < temp->nb_here_doc)
		{
			if (temp->hd_fd[i])
				close(temp->hd_fd[i]);
			i++;
		}
		free_cmd_content(temp);
		tmp2 = temp->next;
		free(temp);
		temp = tmp2;
	}
	free(temp);
}

void	free_cmd_content(t_cmd *lst)
{
	// if (lst->command)
	// 	free(lst->command);
	if (lst->hd_fd)
		free(lst->hd_fd);
	if (lst->hd_file)
		ft_free_map(lst->hd_file);
	if (lst->arg)
		ft_free_map(lst->arg);
	if (lst->limiter)
		ft_free_map(lst->limiter);
}

void	ft_free_p_list(t_parsed **lst, t_data *data)
{
	(void)data;
	t_parsed	*temp;
	t_parsed	*tmp2;
	int			i;

	i = 0;
	temp = (*lst);
	while (temp)
	{
		if (temp->status != COMMAND && temp->status != ARG
				&& temp->status != ECHO && temp->status != PWD
				&& temp->status != CD && temp->status != EXPORT
				&& temp->status != UNSET && temp->status != ENV
				&& temp->status != EXIT && temp->status != LIMITER)
			free(temp->token);
		tmp2 = temp->next;
		free(temp);
		temp = tmp2;
		i++;
	}
	// ft_free_map(data->str_split);
	free(temp);
}

void	ft_free_env(t_env **envp)
{
	t_env	*temp;
	t_env	*tmp2;
	
	temp = (*envp);
	while (temp)
	{
		free(temp->env);
		tmp2 = temp->next;
		free(temp);
		temp = tmp2;
	}
	free(temp);
}

void	ft_free_map(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		// printf("i = %d\n", i);
		free(str[i]);
		i++;
	}
	free(str);	
}

