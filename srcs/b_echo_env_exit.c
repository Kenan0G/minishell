/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_env_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:44:49 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/16 11:45:47 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

		// if (c_list->arg[i + 1] && c_list->quote_status[i + 1] == NO_QUOTE
		// 		&& c_list->quote_status[i] == NO_QUOTE)

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
		{		
			printf("%s", c_list->arg[i]);
			if (c_list->arg[i + 1])
				printf(" ");
		}
		if (!c_list->arg[i])
			break ;
		i++;
	}
	if (newline)
		printf("\n");
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

void	exec_env(t_env *e_list, t_cmd *c_list)
{
	if (!c_list->arg[1] )
		print_env(e_list);
	else
		printf("env: %s: No such file or directory\n", c_list->arg[1]);
}

void	exec_exit(t_cmd *c_list, t_parsed *p_list)
{
	(void)p_list;
	(void)c_list;
	printf("exec_exit\n");
	// exit (0);
}