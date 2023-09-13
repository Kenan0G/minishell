/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:17:01 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/13 15:56:03 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_in_here_doc = 0;

int	main(int ac, char **av, char **env)
{
	t_cmd		*c_list;
	t_parsed	*p_list;
	t_env		*env_list;
	t_data		data;

	(void)av;
	if (ac != 1)
	{
		printf("Error:	to many arguments.\n");
		return (1);
	}
	env_list = NULL;
	c_list = NULL;
	p_list = NULL;
	env_list = get_env(env_list, env);
	run_loop(c_list, p_list, env_list, &data);
	if (env_list)
		ft_free_env(&env_list);
	return (0);
}

int	exit_status_main(int exit_no)
{
	if (g_in_here_doc == 130)
	{
		exit_no = 130;
		g_in_here_doc = 0;
	}
	return (exit_no);
}

void	run_loop(t_cmd *c_list, t_parsed *p_list, t_env *env_list, t_data *data)
{
	char	*str;
	int		exit_no;

	exit_no = 0;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_ctrl_c);
		str = readline("minishell$> ");
		exit_no = exit_status_main(exit_no);
		if (!str)
			break ;
		if (!*str)
		{
			free(str);
			continue ;
		}
		data->str = str;
		data->exit_main = exit_no;
		exit_no = run_loop_2(data, c_list, p_list, env_list);
		add_history(str);
		free(str);
	}
}

int	run_loop_2(t_data *data, t_cmd *c_list, t_parsed *p_list, t_env *env_list)
{
	int	parsing_is_ok;

	parsing_is_ok = check(data->str);
	if (parsing_is_ok == 0)
	{
		init_data(&data, data->exit_main, env_list, data->str);
		p_list = temp_list(data, data->str, env_list);
		c_list = create_cmd_list(p_list, data);
		execution(c_list, p_list, data, &env_list);
		data->exit_main = ft_wait(data);
		ft_end(&c_list, &p_list);
	}
	else
		data->exit_main = parsing_is_ok;
	return (data->exit_main);
}

void	init_data(t_data **data, int exit_no, t_env *env, char *str)
{
	ft_memset((*data), 0, sizeof(t_data));
	(*data)->str = str;
	(*data)->exit_no = exit_no;
	(*data)->envp = env;
	(*data)->c_list_adress = NULL;
}
