/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:06:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 19:20:00 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_env(t_env *token)
{
	t_env	*temp;

	temp = token;
	while (temp)
	{
		if (temp->printable)
			printf("%s\n", temp->env);
		else
			printf("[[[[[[[[[[[[%s]]]]]]]]]]]]]]]]]\n", temp->env);
		temp = temp->next;
	}
}

void	exec_env(t_env *e_list, t_cmd *c_list)
{
	(void)c_list;
	if (!c_list->arg[1])
		print_env(e_list);
	else if (c_list->arg[1][0] == '-' && c_list->arg[1][1] != '\0')
		printf("env: %c%c: Invalid option\n",
			c_list->arg[1][0], c_list->arg[1][1]);
	else if (c_list->arg[1][0] == '-' && c_list->arg[1][1] == '\0')
		return ;
	else
		printf("env: %s: No such file or directory\n", c_list->arg[1]);
}
