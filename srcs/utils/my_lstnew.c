/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:46:16 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 14:48:57 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_cmd	*my_lstnew_cmd(void)
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
