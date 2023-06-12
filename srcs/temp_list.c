/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:03:03 by kgezgin           #+#    #+#             */
/*   Updated: 2023/05/12 14:33:52 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		printf("command = %s\n", temp->command);
		printf("fd_in   = %d\n", temp->fd_in);
		printf("fd_out  = %d\n\n", temp->fd_out);
		temp = temp->next;
	}
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

int	first_char(char *str, int prev_status)
{
	if (str[0] == '<' && str[1] == '\0')
		return (REDIR_IN);
	else if (str[0] == '<' && str[1] == '<')
		return (HERE_DOC);
	else if(str[0] == '>' && str[1] == '\0')
		return (REDIR_OUT);
	else if (str[0] == '>' && str[1] == '>')
		return (APPEND);
	else if(str[0] == '|')
		return (PIPE);
	else
	{
		if (prev_status == REDIR_IN)
			return (FILE_IN);
		else if (prev_status == REDIR_OUT || prev_status == APPEND)
			return (FILE_OUT);
		else if (prev_status == HERE_DOC)
			return (LIMITER);
		else
			return (ARG);
	}
	return (0);
}

void	get_command(t_temp *list, t_data *data)
{
	int		i;
	t_temp	*temp;

	temp = list;
	while (temp)
	{
		i = 0;
		while (temp && temp->status != PIPE)
		{
			if (temp->status == ARG && i == 0)
			{
				temp->status = COMMAND;
				data->cmd_count += 1;
				i++;
			}
			temp = temp->next;
		}
		if (temp == NULL)
			break ;
		else
			temp = temp->next;
	}
}
t_temp *temp_list(t_data *data, char **av, char *str)
{
	t_temp	*list;
	int		i;
	char	**str_split;
	int		status;
	int		prev_status;
	
	i = 0;
	(void)av;
	// (void)str;
	list = NULL;
	prev_status = 0;
	str_split = ft_split(str , ' ');
	// str_split = ft_split(av[1] , ' ');
	while (str_split[i])
	{
		status = first_char(str_split[i], prev_status);
		my_lstadd_back(&list, my_lstnew(str_split[i], status));
		prev_status = status;
		i++;
	}
	get_command(list, data);
	data->parsed_list_size = i;
	// print_list(list);
	// printf("----nombre d'exec = %d\n\n", data->cmd_count);
	// printf("----parsed list size = %d\n", data->parsed_list_size);
	return (list);
}
