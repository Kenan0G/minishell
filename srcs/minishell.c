/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:17:01 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/31 18:54:56 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// gerer le control+C pour les here_doc
// protgerer les writes qvec juste un if (write = -1)

int	in_here_doc= 0;

int main(int ac, char **av, char **env)
{
	t_cmd		*c_list;
	t_parsed	*p_list;
	t_env		*env_list;
	t_data		data;
	char		*str;
	int			parsing_is_ok;
	int			exit_no;

	if (ac != 1)
	{
		printf("Error:	to many arguments.\n");
		return (1);
	}
	env_list = NULL;
	env_list = get_env(env_list, env);
	while (1)
	{
		signal(SIGQUIT, signal_ctrl_backslash);
		signal(SIGINT, signal_ctrl_c);
		str = readline("minishell$> ");
		if (!str)
			break;
		add_history(str);
		parsing_is_ok = check(str);
		if (parsing_is_ok == 0)
		{
			init_data(&data, exit_no);
			p_list = temp_list(&data, av, str, env_list);
			// print_list(p_list);
			c_list = create_cmd_list(p_list, &data);
			// print_cmd_list(c_list);
			execution(c_list, p_list, &data, &env_list);
			exit_no = ft_wait(&data);
			ft_end(&c_list, &p_list, &data, &env_list);
		}
		else
			exit_no = parsing_is_ok;
		free(str);
	}
	if (env_list)
		ft_free_env(&env_list);
	return (0);
}

void init_data(t_data *data, int exit_no)
{
	ft_memset(data, 0, sizeof(t_data));
	data->cmd_count = 0;
	data->pipe_count = 0;
	data->index = 0;
	data->i = 0;
	data->j = 0;
	data->error_status = 0;
	data->exit_no = exit_no;
	data->free_oldpwd = 0;
}

// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=valgrind.txt ./minishell
