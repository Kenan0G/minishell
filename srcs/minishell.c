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

int main (int ac, char **av, char **env)
{
	t_cmd			*cmd_list;
	t_temp			*token;
	t_data			data;

	(void)ac;
	init_data(&data, env);
	token = temp_list(&data, av, av[1]);
	cmd_list = create_cmd_list(token, &data);
	main_exec(cmd_list, &data);
	ft_unlink(cmd_list);
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
