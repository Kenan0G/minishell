/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:45:48 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 14:46:56 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
