/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:59:04 by red               #+#    #+#             */
/*   Updated: 2023/09/12 19:44:49 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_classic(t_cmd *lst, t_parsed *p_list, t_data *data,
		t_env *env_list)
{
	int	res;

	if (ft_isalpha(lst->arg[1][0]))
		exit_char(lst, p_list, data, env_list);
	res = ft_atoi(lst->arg[1]);
	if (ft_strlen(lst->arg[1]) == 19 && lst->arg[1][18] >= '8'
		&& lst->arg[1][18] <= '9')
		exit_char(lst, p_list, data, env_list);
	else if (ft_strlen(lst->arg[1]) == 20 && lst->arg[1][19] == '9')
		exit_char(lst, p_list, data, env_list);
	write(1, "exit\n", 5);
	if (data->cmd_count > 1)
		ft_free_all(data->c_list_adress, data->p_list_adress);
	else
		ft_free_all(&lst, &p_list);
	ft_free_env(&env_list);
	free(data->pid);
	exit(res);
}

void	exit_char(t_cmd *lst, t_parsed *p_list, t_data *data, t_env *env_list)
{
	write(1, "exit\n", 5);
	write(1, "bash: exit: ", 12);
	write(1, lst->arg[1], ft_strlen(lst->arg[1]));
	write(1, ": numeric argument required\n", 28);
	if (data->cmd_count > 1)
		ft_free_all(data->c_list_adress, data->p_list_adress);
	else
		ft_free_all(&lst, &p_list);
	ft_free_env(&env_list);
	free(data->pid);
	exit(2);
}

void	exit_arguments(t_data *data)
{
	write(1, "exit\n", 5);
	write(1, "bash: exit: too many arguments\n", 31);
	data->error_status = 1;
}

void	exec_exit(t_cmd *lst, t_parsed *p_list, t_data *data, t_env *env_list)
{
	if (!ft_strcmp("exit", lst->arg[0]) && !lst->arg[1])
	{
		if (data->cmd_count > 1)
			ft_free_all(data->c_list_adress, data->p_list_adress);
		else
			ft_free_all(&lst, &p_list);
		ft_free_env(&env_list);
		free(data->pid);
		exit(0);
	}
	else if (lst->arg[2] && (lst->arg[1][0] == '-' || lst->arg[1][0] == '+')
			&& (lst->arg[1][1] >= '0' && lst->arg[1][1] <= '9'))
		exit_arguments(data);
	else if (lst->arg[1] && (lst->arg[1][0] >= '0' && lst->arg[1][0] <= '9'
				&& lst->arg[2]))
		exit_arguments(data);
	else if ((lst->arg[1][0] == '-' || lst->arg[1][0] == '+')
			&& (lst->arg[1][1] >= '0' && lst->arg[1][1] <= '9'))
		exit_classic(lst, p_list, data, env_list);
	else if (lst->arg[1] && (lst->arg[1][0] >= '0' && lst->arg[1][0] <= '9'))
		exit_classic(lst, p_list, data, env_list);
	else
		exit_char(lst, p_list, data, env_list);
}
