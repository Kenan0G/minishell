/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:06:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/08 15:20:02 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
