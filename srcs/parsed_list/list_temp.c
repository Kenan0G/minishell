/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:37:49 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 12:41:24 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsed	*temp_list(t_data *data, char *str, t_env *env_list)
{
	t_parsed	*list;
	int			i;
	int			status;
	int			prev_status;

	i = 0;
	list = NULL;
	data->p_list_adress = &list;
	prev_status = 0;
	data->str_split = mr_split(str, "><|", data);
	while (data->str_split[i])
	{
		status = get_status(data->str_split[i], prev_status);
		my_lstadd_back(&list, my_lstnew(data->str_split[i], status));
		prev_status = status;
		i++;
	}
	get_command(list, data, env_list);
	data->parsed_list_size = i;
	if (data->str_split)
		ft_free_map(data->str_split);
	return (list);
}

int	get_status(char *str, int prev_status)
{
	if (str[0] == '<' && str[1] == '\0')
		return (REDIR_IN);
	else if (str[0] == '<' && str[1] == '<')
		return (HERE_DOC);
	else if (str[0] == '>' && str[1] == '\0')
		return (REDIR_OUT);
	else if (str[0] == '>' && str[1] == '>')
		return (APPEND);
	else if (str[0] == '|')
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

int	check_builtin(t_parsed *p_list)
{
	if (!p_list->token)
		return (COMMAND);
	if (!ft_strcmp(p_list->token, "echo"))
		return (ECHO);
	else if (!ft_strcmp(p_list->token, "cd"))
		return (CD);
	else if (!ft_strcmp(p_list->token, "pwd"))
		return (PWD);
	else if (!ft_strcmp(p_list->token, "export"))
		return (EXPORT);
	else if (!ft_strcmp(p_list->token, "unset"))
		return (UNSET);
	else if (!ft_strcmp(p_list->token, "env"))
		return (ENV);
	else if (!ft_strcmp(p_list->token, "exit"))
		return (EXIT);
	else
		return (COMMAND);
}

void	get_command(t_parsed *list, t_data *data, t_env *env_list)
{
	int			i;
	t_parsed	*temp;

	temp = list;
	while (temp)
	{
		i = 0;
		while (temp && temp->status != PIPE)
		{
			run_expand(&temp, env_list, data);
			if (i == 0 && temp->status == ARG && temp->token)
			{
				temp->status = check_builtin(temp);
				data->cmd_count += 1;
				i++;
			}
			temp = temp->next;
		}
		data->pipe_count++;
		if (temp == NULL)
			break ;
		else
			temp = temp->next;
	}
}

void	run_expand(t_parsed **temp, t_env *env_list, t_data *data)
{
	if ((*temp)->status == ARG || (*temp)->status == FILE_IN
		|| (*temp)->status == FILE_OUT)
		(*temp)->token = is_expand((*temp), env_list, data);
}
