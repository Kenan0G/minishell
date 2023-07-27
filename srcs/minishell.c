/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:17:01 by kgezgin           #+#    #+#             */
/*   Updated: 2023/07/27 17:16:35 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// revoir correctement les free et les fd open pour toute les situations
// revoir les leaks sur l'env
// rajouter les signaux
// recuperer le bon code erreur a chaque fois

int main (int ac, char **av, char **env)
{
	t_cmd			*c_list;
	t_parsed		*p_list;
	t_env			*env_list;
	t_data			data;
	char			*str;

	(void)ac;
	env_list = NULL;
	env_list = get_env(env_list, env);
	while (1)
	{
		str = readline("> ");
		add_history(str);
		if (!str)
			break ;
		init_data(&data, env);
		p_list = temp_list(&data, av, str, env_list);
		print_list(p_list);
		c_list = create_cmd_list(p_list, &data);
		execution(c_list, p_list, &data, &env_list);
		ft_end(&c_list, &p_list, &data, &env_list);
		free (str);
	}
	return (0);
}

// void print_parsing(char *str, t_data *data)
// {
// 	char **temp;
// 	int i;

// 	i = 0;
// 	temp = mr_split(str, "><|", data);
// 	while (temp[i])
// 	{
// 		printf("%s\n", temp[i]);
// 		i++;
// 	}
// }

// int main(int ac, char **av, char **env)
// {
// 	t_data data;
// 	char *str;

// 	(void)ac;
// 	(void)av;
// 	(void)env;

// 	str = NULL;
// 	// signal(SIGQUIT, signal_ctrl_backslash);
// 	// signal(SIGINT, signal_ctrl_c);
// 	while (1)
// 	{
// 		str = readline("minishell$> ");
// 		add_history(str);
// 		if (!ft_strcmp("exit", str))
// 			break;
// 		// check(str);
// 		print_parsing(str, &data);
// 	}
// 	return (0);
// }

void	init_data(t_data *data, char **env)
{
	(void)env;
	ft_memset(data, 0, sizeof(t_data));
	data->cmd_count = 0;
	data->index = 0;
	data->i = 0;
	data->j = 0;
}


