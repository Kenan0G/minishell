/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:09:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/01 16:49:24 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		env[i] = temp->env;
		temp = temp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}


char	*get_checked_arg(t_parsed *p_list, t_env *env_list)
{
	if (p_list->token[0] == '\'')
	{
		p_list->quote_status = SIMPLE_QUOTE;
		return (ft_strdup(p_list->token + 1));
	}
	else if (p_list->token[0] == '\"')
	{
		p_list->quote_status = DOUBLE_QUOTE;
		return (is_expand(p_list, env_list));
	}
	else if (p_list->token[0] == '\0')
		return (NULL);
	else
	{
		p_list->quote_status = NO_QUOTE;
		return (is_expand(p_list, env_list));
	}
}

// le cas "$$USER" ou/et "$$" est peut etre a revoir

char	*is_expand(t_parsed *p_list, t_env *env_list)
{
	t_arg	*list;
	int		i;
	
	list = NULL;
	i = 0;
	// a check la condition d'en dessous pour le cas du ""
	if (p_list->token[0] == '"')
		i = 1;
	while (p_list->token[i])
	{
		while (p_list->token[i] && p_list->token[i] != '$')
		{
			my_lstadd_back_arg(&list, my_lstnew_arg(p_list->token[i]));
			i++;
			if (p_list->token[i] == '$' && (p_list->token[i + 1] == ' ' || !p_list->token[i + 1]) && p_list->token[i + 1] != '$')
			{
				my_lstadd_back_arg(&list, my_lstnew_arg('$'));	
				i++;
			}
		}
		if (!p_list->token[i])
			break ;
			// return (ft_strdup(p_list->token + 1));
		i++;
		// printf("p_list->token + i = %s\n", p_list->token + i);
		get_expand_value(p_list->token + i, &list, env_list);
		while (p_list->token[i] != ' ' && p_list->token[i] != '$' && p_list->token[i])
			i++;
		// printf("--p_list->token[i] = %c\n", p_list->token[i]);
	}
	// print_arg(list);
	return (convert_list_to_str(list));
}

char	*convert_list_to_str(t_arg *list)
{
	t_arg	*temp;
	int		len;
	int		i;
	char	*res;

	len = 0;
	i = 0;
	if (!list)
		return (NULL);
	temp = list;
	while (temp)
	{
		len++;
		temp = temp->next;	
	}
	res = malloc(sizeof (char) * (len + 1));
	temp = list;
	while (temp)
	{
		res[i] = temp->c;
		i++;
		temp = temp->next;
	}
	res[i] = '\0';
	// printf("str = %s\n", res);
	return (res);
}

int	get_expand_value(char *str, t_arg **arg_list, t_env *env_list)
{
	t_env	*temp_e;
	int		i;
	int		len;

	temp_e = env_list;
	while (temp_e)
	{
		len = is_permutable(str, temp_e->env);
		if (len > 0)
		{
			i = len + 1;
			while (temp_e->env[i])
			{
				// printf("temp_e->env[i] = %c\n", temp_e->env[i]);
				my_lstadd_back_arg(arg_list, my_lstnew_arg(temp_e->env[i]));
				i++;
			}
			return (len);
		}
		temp_e = temp_e->next;
	}
	return (0);
}

int	is_permutable(char *arg, char *env)
{
	int	i;

	i = 0;
	if (arg[0] == '$')
		return (0);
	while (arg[i] && env[i] && arg[i] == env[i])
		i++;
	if ((arg[i] == ' '|| arg[i] == '$' || !arg[i]) && (env[i] == '=' || !env[i]))
	{
		// printf("arg[i] = %c\nenv[i] = %c\ni = %d\n", arg[i], env[i], i);
		return (i);
	}
	return (0);
}

