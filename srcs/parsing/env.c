/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: red <red@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:37:41 by jsabound          #+#    #+#             */
/*   Updated: 2023/08/27 09:59:09 by red              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	get_env(t_data *data)
// {
// 	t_env	*temp;
// 	int		i;

// 	temp = malloc(sizeof(t_env));
// 	if (!temp)
// 		return ;
// 	i = 0;
// 	data->envp = temp;
// 	while (data->env[i])
// 	{
// 		temp->env = NULL;
// 		temp->env = ft_strjoin(temp->env, data->env[i]);
// 		if (!data->env[i + 1])
// 			temp->next = NULL;
// 		else
// 		{
// 			temp->next = malloc(sizeof(t_env));
// 			if (!temp->next)
// 				return ;
// 			temp = temp->next;
// 		}
// 		i++;
// 	}
// }