// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   init_token.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: red <red@student.42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/30 16:39:10 by jsabound          #+#    #+#             */
// /*   Updated: 2023/07/21 17:21:35 by red              ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// t_token	*lstnew(void *content)
// {
// 	t_token	*new;

// 	new = malloc(sizeof(t_token));
// 	if (!new)
// 		return (NULL);
// 	new->token = content;
// 	new->next = NULL;
// 	return (new);
// }

// void	lstadd_back(t_token **lst, t_token *new)
// {
// 	t_token	*temp;

// 	temp = *lst;
// 	if (!temp)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	else
// 	{
// 		while (temp->next != NULL)
// 			temp = temp->next;
// 		temp->next = new;
// 	}
// }

// void	get_line(char *str, t_data *data)
// {
// 	int i;
// 	char **temp;
// 	t_token *token;

// 	temp = mr_split(str, "><|", data);
// 	printf("temp [0] = %s\n", temp[0]);
// 	printf("temp [1] = %s\n", temp[1]);
// 	token = NULL;
// 	token = malloc(sizeof(t_token));
// 	if (!token)
// 		return ;
// 	data->token = token;
// 	i = 0;
// 	while (temp[i])
// 	{
// 		token->status = 0;
// 		token->token = temp[i];
// 		if (temp[i + 1])
// 		{
// 			token->next = malloc(sizeof(t_token));
// 			if (!token->next)
// 				return ;
// 			token = token->next;
// 		}
// 		else
// 			token->next = NULL;
// 		i++;
// 	}
// }