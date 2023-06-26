/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parsed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:03:03 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/23 18:15:44 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parsed *temp_list(t_data *data, char **av, char *str)
{
	t_parsed	*list;
	int		i;
	char	**str_split;
	int		status;
	int		prev_status;
	
	i = 0;
	(void)av;
	list = NULL;
	prev_status = 0;
	str_split = ft_split(str , ' ');
	while (str_split[i])
	{
		status = first_char(str_split[i], prev_status);
		my_lstadd_back(&list, my_lstnew(str_split[i], status));
		prev_status = status;
		i++;
	}
	get_command(list, data);
	data->parsed_list_size = i;
	return (list);
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

void	get_command(t_parsed *list, t_data *data)
{
	int		i;
	t_parsed	*temp;

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
