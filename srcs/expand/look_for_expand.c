/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_for_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:29:11 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 20:16:22 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*look_for_expand(t_parsed *p_list, t_env *env_list, t_data *data)
{
	t_arg	*list;
	int		i;
	int		ret_exp;

	list = NULL;
	i = 0;
	while (p_list->token[i])
	{
		i = skip_single_quote(i, &list, p_list->token, data);
		if (i == -1)
			break ;
		i = copy_in_list(i, p_list->token, &list, data);
		if (i == -1)
			break ;
		if (p_list->token[i] != '\'')
		{
			i++;
			ret_exp = permute_expand(p_list->token + i, &list, env_list, data);
			i = update_index(p_list->token, i, ret_exp);
			if (!p_list->token[i])
				break ;
		}
	}
	free (p_list->token);
	return (convert_list_to_str(list));
}

int	copy_in_list(int i, char *str, t_arg **list, t_data *data)
{
	(void)data;
	while (str[i] && str[i] != '$' && str[i] != '\'')
	{
		my_lstadd_back_arg(list, my_lstnew_arg(str[i]));
		i++;
	}
	if (!str[i])
		return (-1);
	return (i);
}

int	update_index(char *str, int i, int ret_expand)
{	
	if (ret_expand == -1)
	{
		while (str[i] != '"')
			i++;
	}
	else
		i = i + ret_expand;
	return (i);
}

int	skip_single_quote(int i, t_arg **list, char *str, t_data *data)
{
	(void)data;
	{	
		my_lstadd_back_arg(list, my_lstnew_arg(str[i]));
		i++;
		while (str[i] && str[i] != '\'')
		{
			my_lstadd_back_arg(list, my_lstnew_arg(str[i]));
			i++;
		}
		if (str[i] == '\'')
		{
			my_lstadd_back_arg(list, my_lstnew_arg(str[i]));
			i++;
		}
		if (!str[i])
			return (-1);
	}
	return (i);
}
