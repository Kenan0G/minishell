/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:58:45 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/11 16:36:02 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (lst->command)
		free(lst->command);
	if (lst->arg)
		ft_free_map(lst->arg);
	if (lst->limiter)
		ft_free_map(lst->limiter);
	if (lst->hd_file)
		ft_free_map(lst->hd_file);
	if (lst->hd_fd)
		free(lst->hd_fd);
	if (lst->quote_status)
		free(lst->quote_status);
}

void	ft_free_p_list(t_parsed **lst)
{
	t_parsed	*temp;
	t_parsed	*tmp2;
	int			i;

	i = 0;
	temp = (*lst);
	while (temp)
	{
		if (temp->token)
			free(temp->token);
		tmp2 = temp->next;
		free(temp);
		temp = tmp2;
		i++;
	}
	free(temp);
}

void	ft_free_env(t_env **envp)
{
	t_env	*temp;
	t_env	*tmp2;

	temp = (*envp);
	while (temp)
	{
		if (temp->env)
			free(temp->env);
		tmp2 = temp->next;
		free(temp);
		temp = tmp2;
	}
	free(temp);
}

void	ft_free_arg_list(t_arg **arg)
{
	t_arg	*temp;
	t_arg	*tmp2;

	temp = (*arg);
	while (temp)
	{
		tmp2 = temp->next;
		free(temp);
		temp = tmp2;
	}
	free(temp);
}
