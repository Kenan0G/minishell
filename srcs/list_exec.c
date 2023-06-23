/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:27:17 by jsabound          #+#    #+#             */
/*   Updated: 2023/06/23 18:40:45 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_cmd_list(t_temp *parsed_list, t_data *data)
{
	t_cmd	*cmd_list;
	int		i;

	i = 0;
	cmd_list = NULL;
	while (i != data->cmd_count)
	{
		my_lstadd_back_cmd(&cmd_list, my_lstnew_cmd());
		i++;
	}
	cmd_list = get_value(cmd_list, parsed_list);
	cmd_list = get_fd(cmd_list, parsed_list, data);
	return (cmd_list);
}

t_cmd	*get_value(t_cmd *cmd_list, t_temp *parsed_list)
{
	int		i;
	int		j;
	t_cmd	*c_list;
	t_temp	*p_list;
	
	c_list = cmd_list;
	p_list = parsed_list;
	int k = 0;
	while (c_list)
	{
		i = 0;
		j = 0;
		p_list = get_value_i_j(p_list, &i, &j);
		get_value_malloc(c_list, i, j);

		if (p_list == NULL)
			break ;
		else
			p_list = p_list->next;
		c_list = c_list->next;
		k++;
	}
	get_args(cmd_list, parsed_list);
	return (cmd_list);
}

t_cmd	*get_fd(t_cmd *cmd_list, t_temp *parsed_list, t_data *data)
{
	t_cmd	*c_list;
	t_temp	*p_list;
	
	p_list = parsed_list;
	c_list = cmd_list;
	hd_execution(p_list, c_list);
	while (c_list)
	{
		data->i = 0;
		data->j = 0;
		while (p_list && p_list->status != PIPE)
		{
			ft_open(p_list, c_list, data);
			p_list = p_list->next;
		}
		if (p_list == NULL)
			break ;
		else
			p_list = p_list->next;
		c_list = c_list->next;
	}
	return (cmd_list);
}














