/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exec_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:19:20 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/23 18:35:23 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parsed	*get_value_i_j(t_parsed *p_list, int *i, int *j)
{
	while (p_list && p_list->status != PIPE)
	{
		if (p_list->status == ARG || p_list->status == COMMAND)
			*i = (*i)+ 1;
		else if (p_list->status == HERE_DOC)
			*j = (*j)+ 1;
		p_list = p_list->next;
	}
	return (p_list);
}

void	get_value_malloc(t_cmd *c_list, int i, int j)
{
	c_list->nb_here_doc = j;
	c_list->hd_file = malloc(sizeof(char *) * (j + 1));
	c_list->limiter = malloc(sizeof(char *) * (j + 1));
	c_list->hd_fd = malloc(sizeof(int) * (j));
	c_list->arg = malloc(sizeof(char *) * (i + 1));
}

void	get_args(t_cmd *cmd_list, t_parsed *parsed_list)
{
	int		i;
	int		j;
	t_cmd	*c_list;
	t_parsed	*p_list;
	
	c_list = cmd_list;
	p_list = parsed_list;
	while(c_list)
	{
		i = 0;
		j = 0;
		while (p_list && p_list->status != PIPE)
		{
			get_args_utils(c_list, p_list, &i, &j);
			p_list = p_list->next;
		}
		if (p_list == NULL)
			break ;
		else
			p_list = p_list->next;
		c_list = c_list->next;
	}
}

void	get_args_utils(t_cmd *c_list, t_parsed *p_list, int *i, int *j)
{
	if (p_list->status == COMMAND)
	{
		c_list->command = p_list->token;
		c_list->arg[*i] = p_list->token;
		(*i)++;
	}
	else if (p_list->status == ARG)
	{
		c_list->arg[*i] = p_list->token;
		(*i)++;
	}
	else if (p_list->status == LIMITER)
	{
		c_list->limiter[*j] = p_list->token;
		(*j)++;
	}
	c_list->limiter[*j] = NULL;
	c_list->arg[*i] = NULL;
}