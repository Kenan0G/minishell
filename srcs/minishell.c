/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:17:01 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 17:31:29 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// normer ...

// cat
// control + C
// control + D


//  ________________________________________________________________________________
// |																				|
// | voir les expand dans le here doc												|
// | -> le probleme c que si je fait ca je pourrais pas free_all dans le			|
// | 	  fork du here_doc															|
// | 																				|
// | re split les arg sur espace apres avoir gerer les expands					 	|
// | -> le probleme c que je dois split seulement quand il y a un ou des espaces	|
// | 	  dans un expand.donc par exemple ls "srcs includes" ne doit pas etre split	|
// |________________________________________________________________________________|

int	g_in_here_doc = 0;

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

void	run_loop(t_cmd *c_list, t_parsed *p_list, t_env *env_list, t_data *data)
{
	char		*str;
	int			parsing_is_ok;
	int			exit_no;

	exit_no = 0;
	while (1)
	{
		signal(SIGQUIT, signal_ctrl_backslash);
		signal(SIGINT, signal_ctrl_c);
		str = readline("minishell$> ");
		if (g_in_here_doc == 130)
			exit_no = 130;
		if (!str)
			break;
		if (!*str)
		{
			free(str);
			continue;
		}
		add_history(str);
		parsing_is_ok = 0;
		if (parsing_is_ok == 0)
		{
			init_data(&data, exit_no, env_list);
			p_list = temp_list(data, str, env_list);
			c_list = create_cmd_list(p_list, data);
			execution(c_list, p_list, data, &env_list);
			exit_no = ft_wait(data);
			ft_end(&c_list, &p_list);
		}
		else
			exit_no = parsing_is_ok;
		free(str);
	}
}

void init_data(t_data **data, int exit_no, t_env *env)
{
	ft_memset((*data), 0, sizeof(t_data));
	(*data)->exit_no = exit_no;
	(*data)->envp = env;
	(*data)->c_list_adress = NULL;
}

// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=valgrind.txt ./minishell
