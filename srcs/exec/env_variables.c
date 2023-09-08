/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:09:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/08 17:22:17 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_char(t_env *env_list)
{
	t_env	*temp;
	char	**env;
	int		i;

	i = 0;
	temp = env_list;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	temp = env_list;
	while (temp)
	{
		env[i] = ft_strdup(temp->env);
		temp = temp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}


char	*get_checked_arg(t_parsed *p_list, t_env *env_list, t_data *data)
{
	if (p_list->token[0] == '\"' || p_list->token[0] == '\'')
	{
		p_list->quote_status = DOUBLE_QUOTE;
		return (is_expand(p_list, env_list, data));
	}
	else if (p_list->token[0] == '\0')
		return (ft_strdup(p_list->token));
	else
	{
		p_list->quote_status = NO_QUOTE;
		return (is_expand(p_list, env_list, data));
	}
}

// le cas "$$USER" ou/et "$$" est peut etre a revoir

char	*is_expand(t_parsed *p_list, t_env *env_list, t_data *data)
{
	t_arg	*list;
	int		i;
	int		ret_expend;

	list = NULL;
	i = 0;
	while (p_list->token[i])
	{
		if (p_list->token[i] == '\'')
		{
			my_lstadd_back_arg(&list, my_lstnew_arg(p_list->token[i]));
			i++;
			while (p_list->token[i] && p_list->token[i] != '\'')
			{
				my_lstadd_back_arg(&list, my_lstnew_arg(p_list->token[i]));
				i++;
			}
			my_lstadd_back_arg(&list, my_lstnew_arg(p_list->token[i]));
			i++;
			if (!p_list->token[i])
				break ;
		}
		while (p_list->token[i] && p_list->token[i] != '$' && p_list->token[i] != '\'')
		{
			my_lstadd_back_arg(&list, my_lstnew_arg(p_list->token[i]));
			i++;
		}
		if (!p_list->token[i])
			break ;
		else if (p_list->token[i] != '\'')
		{
			i++;
			ret_expend = get_expand_value(p_list->token + i, &list, env_list, data);
			if ( ret_expend == -1)
			{
				while (p_list->token[i] != '"')
					i++;
			}
			else
				i = i + ret_expend;
			if (!p_list->token[i])
				break ;
		}
	}
	free (p_list->token);
	// print_arg(list);
	return (convert_list_to_str(list));
}

int	get_expand_value(char *str, t_arg **arg_list, t_env *env_list, t_data *data)
{
	t_env	*temp_e;
	int		i;
	int		len;

	temp_e = env_list;
	i = 0;
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
	while (temp_e)
	{
		if (temp_e->printable == 1)
			len = is_permutable(str, temp_e->env);
		else
			len = 0;
		if (len > 0)
		{
			i = len + 1;
			while (temp_e->env[i])
			{
				my_lstadd_back_arg(arg_list, my_lstnew_arg(temp_e->env[i]));
				i++;
			}
			return (len);
		}
		temp_e = temp_e->next;
	}
	return (ret_expend(str));
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
int	ret_expend(char *str)
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
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '$' && str[i] != '"')
		i++;
	return (i);
}

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
	if (i > 0 && arg[i - 1] && env[i - 1] && arg[i - 1] == '=' && env[i - 1] == '=')
		j = i - 1;
	// if ((arg[j] == ' ' || arg[j] == '\t' || arg[j] == '$' || arg[j] == '"'
			// || arg[j] == '\'' || arg[j] == '.' || arg[j] == '=' || !arg[j])
			// && (env[j] == '=' || !env[j]))
	if (!ft_isalnum(arg[j]) && (env[j] == '=' || !env[j]))
		return (j);
	return (0);
}

char	*convert_list_to_str(t_arg *list)
{
	char	*res;
	int		*tab;

	if (!list)
		return (NULL);
	tab = get_char_status(list, get_tab_len(list));
	res = malloc(sizeof (char) * (str_malloc_len(tab, get_tab_len(list)) + 1));
	res = get_res(list, tab, res);
	free(tab);
	ft_free_arg_list(&list);
	return (res);
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

int	str_malloc_len(int *tab, int tablen)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < tablen)
	{
		if (tab[i] == 0)
			len++;
		i++;
	}
	return (len);
}

int	get_tab_len(t_arg *list)
{
	int		len;
	t_arg	*temp;

	len = 0;
	temp = list;
	while (temp)
	{
		len++;
		temp = temp->next;	
	}
	return (len);
}

int	*get_char_status(t_arg *list, int tablen)
{
	t_arg	*temp;
	int		i;
	int		*tab;

	tab = malloc(sizeof(int) * tablen);
	temp = list;
	i = 0;
	while (temp)
	{
		if (temp->c == '"')
		{
			tab[i] = 1;
			i++;
			temp = temp->next;
			while (temp && temp->c != '"')
			{
				tab[i] = 0;
				i++;
				temp = temp->next;
			}
			if (i < tablen)
				tab[i] = 1;
		}
		else if (temp->c == '\'')
		{
			tab[i] = 1;
			i++;
			temp = temp->next;
			while (temp && temp->c != '\'')
			{
				tab[i] = 0;
				i++;
				temp = temp->next;
			}
			if (i < tablen)
				tab[i] = 1;
		}
		else
			tab[i] = 0;
		i++;
		temp = temp->next;
	}
	return(tab);
}

int	get_len(char **arg, int bool)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[j])
		{
			if (arg[i][j] == ' ' && bool == 1)
				len++;
			j++;
		}
		len++;
		i++;
	}
	return (len);
}

char	**arg_update(char **arg)
{
	int		len;
	char	**new;

	len = get_len(arg, 1);
	if (len == get_len(arg, 2))
		return (arg);
	new = malloc(sizeof(char *) * len + 1);
	if (!new)
		return (arg);
	return (new_arg(arg, new));
}

char	**new_arg(char **arg, char **new)
{
	char	**temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (arg[i])
	{
		j = 0;
		temp = ft_split(arg[i], ' ');
		while (temp[j])
		{
			new[k] = ft_strdup(temp[j]);
			k++;
			j++;
		}
		if (temp)
			ft_free_map(temp);
		i++;
	}
	new[k] = NULL;
	return (new);
}