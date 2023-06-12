/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:25:49 by red               #+#    #+#             */
/*   Updated: 2023/05/19 11:50:39 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*lstnew(void *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = content;
	new->next = NULL;
	return (new);
}

void	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	temp = *lst;
	if (!temp)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void    get_line(char *str, t_data *data)
{
    int i;
    char **temp;
    t_token *token;
    
    i = 0;
    temp = mr_split(str, " ><|");
    token = NULL;
    while (temp[i])
    {
        lstadd_back(&token, lstnew(temp[i]));
        i++;
    }
    data->token = token;
}

void	print_parsing(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		printf("str =		%s\n", temp->token);
		temp = temp->next;
	}
}

int main (int ac, char **av)
{
    t_data data;
    
    (void)ac;
    get_line(av[1], &data);
    print_parsing(data.token);
    return (0);
}