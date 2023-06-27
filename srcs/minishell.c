/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:17:01 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/23 18:18:01 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// revoir correctement les free et les fd open pour toute les situations

int main (int ac, char **av, char **env)
{
	t_cmd			*c_list;
	t_parsed			*p_list;
	t_data			data;

	(void)ac;
	init_data(&data, env);
	p_list = temp_list(&data, av, av[1]);
	c_list = create_cmd_list(p_list, &data);
	execution(c_list, p_list, &data);
	ft_end(&c_list, &p_list, &data);
	return (0);
}

void	init_data(t_data *data, char **env)
{
	ft_memset(data, 0, sizeof(t_data));
	data->cmd_count = 0;
	data->env = env;
	data->i = 0;
	data->j = 0;
}
