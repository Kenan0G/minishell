/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permute_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:53:42 by kgezgin           #+#    #+#             */
/*   Updated: 2023/12/13 13:29:53 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	permute_expand(char *str, t_arg **arg_list, t_env *env_list, t_data *data)
{
	t_env	*temp_e;
	int		i;
	int		len;
	int		ret_special_cases;

	temp_e = env_list;
	i = 0;
	ret_special_cases = special_cases(arg_list, str, data);
	if (ret_special_cases < 10)
		return (ret_special_cases);
	while (temp_e)
	{
		if (temp_e->printable == 1)
			len = is_permutable(str, temp_e->env);
		else
			len = 0;
		if (len > 0)
			return (permute(i, len, temp_e->env, arg_list));
		temp_e = temp_e->next;
	}
	return (var_len(str));
}

int	special_cases(t_arg **arg_list, char *str, t_data *data)
{
	if (!str[0] || str[0] == ' ' || str[0] == '\t')
	{
		my_lstadd_back_arg(arg_list, my_lstnew_arg('$'));
		return (0);
	}
	else if (str[0] == '"' && !str[1])
	{
		my_lstadd_back_arg(arg_list, my_lstnew_arg('$'));
		return (-1);
	}
	else if (str[0] == '"' && nb_quote(str) % 2 == 0)
		return (0);
	else if (str[0] == '"' && nb_quote(str) % 2 == 1)
	{
		my_lstadd_back_arg(arg_list, my_lstnew_arg('$'));
		return (0);
	}
	else if (str[0] == '?')
	{
		get_fork_status(arg_list, data);
		return (1);
	}
	return (10);
}

	// if ((arg[j] == ' ' || arg[j] == '\t' || arg[j] == '$' || arg[j] == '"'
			// || arg[j] == '\'' || arg[j] == '.' || arg[j] == '=' || !arg[j])
			// && (env[j] == '=' || !env[j]))
int	is_permutable(char *arg, char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (arg[0] == '$')
		return (0);
	while (arg[i] && env[i] && arg[i] == env[i])
		i++;
	j = i;
	if (i > 0 && arg[i - 1] && env[i - 1] && arg[i - 1] == '='
		&& env[i - 1] == '=')
		j = i - 1;
	if (!ft_isalnum(arg[j]) && (env[j] == '=' || !env[j]))
		return (j);
	return (0);
}

int	permute(int i, int len, char *str, t_arg **arg_list)
{	
	i = len + 1;
	while (str[i])
	{
		my_lstadd_back_arg(arg_list, my_lstnew_arg(str[i]));
		i++;
	}
	return (len);
}

int	var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"')
			i++;
		return (i + 1);
	}
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '$'
		&& str[i] != '"')
		i++;
	return (i);
}
