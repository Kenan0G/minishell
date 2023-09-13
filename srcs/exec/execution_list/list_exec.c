/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:27:17 by jsabound          #+#    #+#             */
/*   Updated: 2023/09/13 14:21:36 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_cmd	*create_cmd_list(t_parsed *parsed_list, t_data *data)
{
	t_cmd	*cmd_list;
	int		i;

	i = 0;
	cmd_list = NULL;
	while (i != data->pipe_count)
	{
		my_lstadd_back_cmd(&cmd_list, my_lstnew_cmd());
		i++;
	}
	cmd_list = get_value(cmd_list, parsed_list);
	data->c_list_adress = &cmd_list;
	cmd_list = get_fd(cmd_list, parsed_list, data);
	return (cmd_list);
}

t_cmd	*get_value(t_cmd *cmd_list, t_parsed *parsed_list)
{
	int			i;
	int			j;
	int			k;
	t_cmd		*c_list;
	t_parsed	*p_list;

	c_list = cmd_list;
	p_list = parsed_list;
	k = 0;
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

t_cmd	*get_fd(t_cmd *cmd_list, t_parsed *parsed_list, t_data *data)
{
	t_cmd		*c_list;
	t_parsed	*p_list;

	p_list = parsed_list;
	c_list = cmd_list;
	run_here_doc(c_list, p_list, data);
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

void	run_here_doc(t_cmd *c_list, t_parsed *p_list, t_data *data)
{	
	g_in_here_doc = 1;
	if (hd_execution(p_list, c_list, data) == -1)
		data->dont_loop = 1;
	data->error_status = data->here_doc_exit;
	if (data->dont_loop == 1)
		g_in_here_doc = 130;
	else
		g_in_here_doc = 0;
}
