/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:09:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/09 17:53:30 by kgezgin          ###   ########.fr       */
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
		env[i] = ft_strdup(temp->env);
		temp = temp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}


char	*get_checked_arg(t_parsed *p_list, t_env *env_list)
{
	char	*res;

	if (p_list->token[0] == '\'')
	{
		p_list->quote_status = SIMPLE_QUOTE;
		res = ft_strdup(p_list->token + 1);
		free(p_list->token);
		return (res);
	}
	else if (p_list->token[0] == '\"')
	{
		p_list->quote_status = DOUBLE_QUOTE;
		return (is_expand(p_list, env_list));
	}
	else if (p_list->token[0] == '\0')
		return (p_list->token);
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
	int		ret_expend;

	list = NULL;
	i = 0;
	while (p_list->token[i])
	{
		while (p_list->token[i] && p_list->token[i] != '$')
		{
			my_lstadd_back_arg(&list, my_lstnew_arg(p_list->token[i]));
			i++;
		}
		if (!p_list->token[i])
			break ;
		// else if (p_list->token[i] == '$' && !p_list->token[i + 1])
		// {
		// 	my_lstadd_back_arg(&list, my_lstnew_arg(p_list->token[i]));
		// 	i++;
		// }
		// else if (p_list->token[i] == '$' && p_list->token[i + 1] == '"' && !p_list->token[i + 2])
		// {
		// 	my_lstadd_back_arg(&list, my_lstnew_arg(p_list->token[i]));
		// 	i++;
		// }
		// else
		// {
		i++;
		ret_expend = get_expand_value(p_list->token + i, &list, env_list);
		if ( ret_expend == -1)
		{
			while (p_list->token[i] != '"')
				i++;
		}
		else
		{
			i = i + ret_expend;
			// while (p_list->token[i] && p_list->token[i] != ' ' && p_list->token[i] != '$') // && (p_list->token[i] != '"' && !p_list->token[i + 1])) // quand je fait echo "$", quand on arrive ici on rentre jamais dans la boucle en gros a gere echo "$"
			// while (ret_expend != 0)
			// {
			// 	ret_expend--;
			// 	i++;
			// }
		}
		printf("a la sortie de du if, on est sur [%c] et cleui d'avant c = [%c]\n", p_list->token[i], p_list->token[i - 1]);
		if (!p_list->token[i])
			break ;
		// } 
		// else if (p_list->token[i] == '$' && (p_list->token[i + 1] == '\0' || p_list->token[i + 1] != ' '|| p_list->token[i + 1] != ' ' || p_list->token[i + 1] != '"'))
		// {
		// 	printf("test dollar\n\n");
		// 	my_lstadd_back_arg(&list, my_lstnew_arg('$'));	
		// 	i++;
		// }
		// printf("p_list->token + i = %s\n", p_list->token + i);
		// printf("--p_list->token[i] = %c\n", p_list->token[i]);
	}
	free (p_list->token);
	print_arg(list);
	return (convert_list_to_str(list));
}

int	get_expand_value(char *str, t_arg **arg_list, t_env *env_list)
{
	t_env	*temp_e;
	int		i;
	int		len;

	temp_e = env_list;
	i = 0;
	if (!str[0] || str[0] == ' ')
	{
		my_lstadd_back_arg(arg_list, my_lstnew_arg('$'));
		i++;
		return (0);
	}
	else if(str[0] == '"' && !str[1])
	{
		printf("test if \n\n");
		my_lstadd_back_arg(arg_list, my_lstnew_arg('$'));
		i++;
		return (-1);
	}
	while (temp_e)
	{
		len = is_permutable(str, temp_e->env);
		if (len > 0)
		{
			i = len + 1;
			while (temp_e->env[i])
			{
				printf("temp_e->env[i] = %c\n", temp_e->env[i]);
				my_lstadd_back_arg(arg_list, my_lstnew_arg(temp_e->env[i]));
				i++;
			}
			return (len);
		}
		temp_e = temp_e->next;
	}
	return (ret_expend(str));
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
	while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '"')
		i++;
	printf("i = %d\n", i);
	return (i);
}

int	is_permutable(char *arg, char *env)
{
	int	i;

	i = 0;
	printf("arg = %s\n", arg);
	if (arg[0] == '$')
		return (0);
	while (arg[i] && env[i] && arg[i] == env[i])
		i++;
	if ((arg[i] == ' '|| arg[i] == '$' || arg[i] == '"' || !arg[i]) && (env[i] == '=' || !env[i]))
	{
		// printf("arg[i] = %c\nenv[i] = %c\ni = %d\n", arg[i], env[i], i);
		return (i);
	}
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
	// printf("str = %s\n", res);
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
	// printf("malloc_len = %d\n", len);
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
	// i = 0;
	// temp = list;
	// while (temp)
	// {
	// 	printf("[%c]\ntab[%d] = %d\n",temp->c,  i, tab[i]);
	// 	temp = temp->next;
	// 	i++;
	// }
	return(tab);
}
