/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exec_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:19:20 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/11 16:48:32 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_parsed	*get_value_i_j(t_parsed *p_list, int *i, int *j)
{
	while (p_list && p_list->status != PIPE)
	{
		if (p_list->status == ARG
			|| p_list->status == COMMAND || p_list->status == ECHO
			|| p_list->status == PWD || p_list->status == CD
			|| p_list->status == EXPORT || p_list->status == UNSET
			|| p_list->status == ENV || p_list->status == EXIT)
			*i = (*i) + 1;
		else if (p_list->status == HERE_DOC)
			*j = (*j) + 1;
		p_list = p_list->next;
	}
	return (p_list);
}

void	get_value_malloc(t_cmd *c_list, int i, int j)
{
	c_list->nb_here_doc = j;
	c_list->hd_file = ft_calloc(sizeof(char *), (j + 1));
	c_list->limiter = malloc(sizeof(char *) * (j + 1));
	if (!c_list->limiter)
		c_list->limiter = NULL;
	c_list->hd_fd = ft_calloc(sizeof(int), j);
	c_list->arg = malloc(sizeof(char *) * (i + 1));
	if (!c_list->arg)
		c_list->arg = NULL;
	c_list->quote_status = malloc(sizeof(int) * (i));
	if (!c_list->quote_status)
		c_list->quote_status = NULL;
}

void	get_args(t_cmd *cmd_list, t_parsed *parsed_list)
{
	int			i;
	int			j;
	t_cmd		*c_list;
	t_parsed	*p_list;

	c_list = cmd_list;
	p_list = parsed_list;
	while (c_list)
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
	if (p_list->status == COMMAND || p_list->status == ECHO
		|| p_list->status == PWD || p_list->status == CD
		|| p_list->status == EXPORT || p_list->status == UNSET
		|| p_list->status == ENV || p_list->status == EXIT)
	{
		c_list->command = ft_strdup(p_list->token);
		c_list->command_int = p_list->status;
		c_list->arg[*i] = ft_strdup(p_list->token);
		(*i)++;
	}
	else if (p_list->status == ARG)
		*i = check_arg(c_list, p_list, *i);
	else if (p_list->status == LIMITER)
	{
		c_list->limiter[*j] = ft_strdup(p_list->token);
		(*j)++;
	}
	c_list->limiter[*j] = NULL;
	c_list->arg[*i] = NULL;
}

int	check_arg(t_cmd *c_list, t_parsed *p_list, int i)
{
	if (!p_list->token)
	{
		c_list->arg[i] = malloc(sizeof(char) * 1);
		if (!c_list->arg[i])
			return (i);
		c_list->arg[i][0] = '\0';
	}
	else
		c_list->arg[i] = ft_strdup(p_list->token);
	c_list->quote_status[i] = p_list->quote_status;
	i++;
	return (i);
}
