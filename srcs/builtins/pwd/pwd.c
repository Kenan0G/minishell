/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:01:00 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/08 15:40:09 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exec_pwd(t_cmd *c_list)
{
	char	*buf;
	char	*str;

	buf = NULL;
	if (c_list->arg[1] && c_list->arg[1][0] == '-' && c_list->arg[1][1] != '\0')
	{
		printf("pwd: %c%c: Invalid option\n",
			c_list->arg[1][0], c_list->arg[1][1]);
		return ;
	}
	str = getcwd(buf, 0);
	if (!str)
	{
		perror("pwd: error retrieving current directory:"
			" getcwd: cannot access parent directories");
		return ;
	}
	printf("%s\n", str);
	free(str);
}
