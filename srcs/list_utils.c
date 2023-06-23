/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:12:21 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/23 18:35:23 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{	
	t_cmd	*current_node;

	current_node = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new;
}

t_cmd	*my_lstnew_cmd()
{
	t_cmd	*liste;

	liste = malloc(sizeof(*liste));
	liste->next = NULL;
	liste->fd_in = 0;
	liste->fd_out = 0;
	liste->is_ok = 1;
	return (liste);
}

void	my_lstadd_back(t_temp **lst, t_temp *new)
{	
	t_temp	*current_node;

	current_node = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new;
}

t_temp	*my_lstnew(char *content, int status)
{
	t_temp	*liste;

	liste = malloc(sizeof(*liste));
	liste->token = content;
	liste->status = status;
	liste->next = NULL;
	return (liste);
}

void	print_list(t_temp *token)
{
	t_temp	*temp;

	temp = token;
	while (temp)
	{
		printf("str =		%s\n", temp->token);
		printf("status =	%d\n\n", temp->status);

		temp = temp->next;
	}
}

void	print_cmd_list(t_cmd *token)
{
	int		i;
	t_cmd	*temp;

	temp = token;
	while (temp)
	{
		// i = 0;
		// while (temp->arg[i])
		// {
		// 	printf("arg[%d]  = %s\n", i, temp->arg[i]);
		// 	i++;
		// }
		// i = 0;
		// while (temp->limiter[i])
		// {
		// 	printf("limiter[%d]  = %s\n", i, temp->limiter[i]);
		// 	i++;
		// }
		i = 0;
		while (temp->hd_fd[i])
		{
			printf("temp->hd_fd[i] = %d\n", temp->hd_fd[i]);
			i++;
		}
		i = 0;
		while (temp->hd_file[i])
		{
			printf("temp->hd_file[i] = %s\n", temp->hd_file[i]);
			i++;
		}
		// printf("command = %s\n", temp->command);
		// printf("fd_in   = %d\n", temp->fd_in);
		// printf("fd_out  = %d\n\n", temp->fd_out);
		temp = temp->next;
	}
}