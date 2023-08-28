/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:17:01 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/28 14:10:18 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// gerer le control+C pour les here_doc
// faire la fonction de parsing sur le export qui va etre utilisé aussi sur le unset
// faire en sorte que le exit soit executé dans un fork quand il y a un pipe donc il faut l'appeler dans la fonction execution


// Problème CTRL + D, sûrement déjà géré dans l'exec à revoir
// j'ai pas de probleme sur le CTRL + D perso

int main(int ac, char **av, char **env)
{
	t_cmd		*c_list;
	t_parsed	*p_list;
	t_env		*env_list;
	t_data		data;
	char		*str;
	int			parsing_is_ok;

	if (ac != 1)
	{
		printf("Error:	to many arguments.\n");
		return (1);
	}
	env_list = NULL;
	env_list = get_env(env_list, env);
	signal(SIGQUIT, signal_ctrl_backslash);
	signal(SIGINT, signal_ctrl_c);
	while (1)
	{
		str = readline("minishell$> ");
		if (!str)
			break;
		add_history(str);
		parsing_is_ok = check(str);
		if (parsing_is_ok == 0)
		{
			init_data(&data, env);
			p_list = temp_list(&data, av, str, env_list);
			// print_list(p_list);
			c_list = create_cmd_list(p_list, &data);
			// print_cmd_list(c_list);
			execution(c_list, p_list, &data, &env_list);
			ft_end(&c_list, &p_list, &data, &env_list);
		}
		else
			exit_status = parsing_is_ok;
		free(str);
	}
	if (env_list)
		ft_free_env(&env_list);
	return (0);
}

void init_data(t_data *data, char **env)
{
	(void)env;
	ft_memset(data, 0, sizeof(t_data));
	data->cmd_count = 0;
	data->pipe_count = 0;
	data->index = 0;
	data->i = 0;
	data->j = 0;
	data->error_status = 0;
	data->free_oldpwd = 0;
}

// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=valgrind.txt ./minishell
