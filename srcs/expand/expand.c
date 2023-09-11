/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:09:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/11 13:25:39 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*is_expand(t_parsed *p_list, t_env *env_list, t_data *data)
{
	if (p_list->token[0] == '\"' || p_list->token[0] == '\'')
	{
		p_list->quote_status = DOUBLE_QUOTE;
		return (look_for_expand(p_list, env_list, data));
	}
	else if (p_list->token[0] == '\0')
		return (ft_strdup(p_list->token));
	else
	{
		p_list->quote_status = NO_QUOTE;
		return (look_for_expand(p_list, env_list, data));
	}
}

char	*convert_list_to_str(t_arg *list)
{
	char	*res;
	int		*tab;
	int		tablen;

	if (!list)
		return (NULL);
	tablen = get_tab_len(list);
	tab = get_status_tab(list, tablen);
	res = malloc(sizeof (char) * (str_malloc_len(tab, tablen) + 1));
	if (!res)
		return (NULL);
	res = get_res(list, tab, res);
	free(tab);
	ft_free_arg_list(&list);
	return (res);
}

void	get_fork_status(t_arg **arg_list, t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_itoa(data->exit_no);
	while (str[i])
	{
		my_lstadd_back_arg(arg_list, my_lstnew_arg(str[i]));
		i++;
	}
	free(str);
}

int	nb_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"')
			j++;
		i++;
	}
	return (j);
}

char	*get_res(t_arg *list, int *tab, char *res)
{
	t_arg	*temp;
	int		i;
	int		j;

	temp = list;
	i = 0;
	j = 0;
	while (temp)
	{
		if (tab[i] == 0)
		{
			res[j] = temp->c;
			j++;
		}
		i++;
		temp = temp->next;
	}
	res[j] = '\0';
	return (res);
}

// int	get_len(char **arg, int bool)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (arg[i])
// 	{
// 		j = 0;
// 		while (arg[j])
// 		{
// 			if (arg[i][j] == ' ' && bool == 1)
// 				len++;
// 			j++;
// 		}
// 		len++;
// 		i++;
// 	}
// 	return (len);
// }

// char	**arg_update(char **arg)
// {
// 	int		len;
// 	char	**new;

// 	len = get_len(arg, 1);
// 	if (len == get_len(arg, 2))
// 		return (arg);
// 	new = malloc(sizeof(char *) * len + 1);
// 	if (!new)
// 		return (arg);
// 	return (new_arg(arg, new));
// }

// char	**new_arg(char **arg, char **new)
// {
// 	char	**temp;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	k = 0;
// 	while (arg[i])
// 	{
// 		j = 0;
// 		temp = ft_split(arg[i], ' ');
// 		while (temp[j])
// 		{
// 			new[k] = ft_strdup(temp[j]);
// 			k++;
// 			j++;
// 		}
// 		if (temp)
// 			ft_free_map(temp);
// 		i++;
// 	}
// 	new[k] = NULL;
// 	return (new);
// }