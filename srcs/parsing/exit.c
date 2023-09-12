/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:59:04 by red               #+#    #+#             */
/*   Updated: 2023/09/12 13:36:08 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_classic(char *str)
{
	int	res;

	res = ft_atoi(str + 5);
	if (!res)
		exit_char(str);
	write(1, "exit\n", 5);
	// if (res > 255)
	//     res = res / 255;
	exit(res);
}

void	exit_char(char *str)
{
	int	i;

	i = 5;
	write(1, "exit\n", 5);
	write(1, "bash: exit: ", 12);
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, ": numeric argument required\n", 28);
	exit(2);
}

// ne pas check str[5] mais check le charactere apres avoir sauté tout les espaces et tout les tabs

void	exec_exit(char *str)
{
	if (!ft_strcmp("exit", str))
		exit(0);
	else if (str[5] >= '0' && str[5] <= '9')
		exit_classic(str);
	else
		exit_char(str);
}