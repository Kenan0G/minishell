/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:12:21 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/11 14:59:26 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_lstadd_back_env(t_env **lst, t_env *new)
{	
	t_env	*current_node;

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

t_env	*my_lstnew_env(char *str, int nb)
{
	t_env	*liste;

	liste = malloc(sizeof(*liste));
	if (!liste)
		return (NULL);
	liste->next = NULL;
	liste->printable = nb;
	liste->env = ft_strdup(str);
	return (liste);
}

void	my_lstadd_back_arg(t_arg **lst, t_arg *new)
{	
	t_arg	*current_node;

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

t_arg	*my_lstnew_arg(char c)
{
	t_arg	*liste;

	liste = malloc(sizeof(*liste));
	if (!liste)
		return (NULL);
	liste->next = NULL;
	liste->c = c;
	return (liste);
}

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
	if (!liste)
		return (NULL);
	liste->next = NULL;
	liste->arg = NULL;
	liste->command = NULL;
	liste->hd_file = NULL;
	liste->quote_status = NULL;
	liste->hd_fd = NULL;
	liste->limiter = NULL;
	liste->err_no = 0;
	liste->command_int = 0;
	liste->fd_in = 0;
	liste->fd_out = 0;
	liste->is_ok = 1;
	return (liste);
}

void	my_lstadd_back(t_parsed **lst, t_parsed *new)
{	
	t_parsed	*current_node;

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

t_parsed	*my_lstnew(char *content, int status)
{
	t_parsed	*liste;

	liste = malloc(sizeof(*liste));
	if (!liste)
		return (NULL);
	liste->token = ft_strdup(content);
	liste->status = status;
	liste->next = NULL;
	return (liste);
}

void	print_list(t_parsed *token)
{
	t_parsed	*temp;

	temp = token;
	while (temp)
	{
		printf("str =		%s\n", temp->token);
		printf("status =	%d\n\n", temp->status);

		temp = temp->next;
	}
}

void	print_env(t_env *token)
{
	t_env	*temp;

	temp = token;
	while (temp)
	{
		if (temp->printable)
			printf("%s\n", temp->env);
		else
			printf("[[[[[[[[[[[[%s]]]]]]]]]]]]]]]]]\n", temp->env);
		temp = temp->next;
	}
}

void	print_arg(t_arg *token)
{
	t_arg	*temp;

	temp = token;
	while (temp)
	{
		printf("[%c]", temp->c);
		temp = temp->next;
	}
	printf("\n");
}

void	print_cmd_list(t_cmd *token)
{
	int		i;
	t_cmd	*temp;

	temp = token;
	while (temp)
	{
		i = 0;
		while (temp->arg[i])
		{
			printf("arg[%d]  = %s\n", i, temp->arg[i]);
			i++;
		}
		i = 0;
		while (temp->limiter[i])
		{
			printf("limiter[%d]  = %s\n", i, temp->limiter[i]);
			i++;
		}
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
		printf("command = %s\n", temp->command);
		printf("fd_in   = %d\n", temp->fd_in);
		printf("fd_out  = %d\n\n", temp->fd_out);
		temp = temp->next;
	}
}