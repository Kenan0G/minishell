/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:06:29 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/08 15:19:35 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exec_echo(t_cmd *c_list)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (c_list->arg[i])
	{
		if (i == 1)
		{	
			while (c_list->arg[i] && check_param_echo(c_list->arg[i]))
			{
				newline = 0;
				i++;
			}
		}
		if (c_list->arg[i])
			display(c_list, i);
		if (!c_list->arg[i])
			break ;
		i++;
	}
	if (newline)
		printf("\n");
}

void	display(t_cmd *c_list, int i)
{	
	printf("%s", c_list->arg[i]);
	if (c_list->arg[i + 1])
		printf(" ");
}

int	check_param_echo(char *str)
{
	int	i;

	i = 1;
	if (!str[0] || !str[1] || str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
