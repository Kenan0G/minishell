/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:09:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/07/28 13:21:14 by kgezgin          ###   ########.fr       */
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



// int	env_var_len(char *var_tmp, t_env *env_list)
// {
// 	t_env	*temp;

// 	temp = env_list;
// 	while (temp)
// 	{
// 		if (!ft_strncmp(temp->env, var_tmp, ft_strlen(var_tmp)) 
// 				&& ft_strlen(var_tmp) == get_lenght(temp->env, '='))
// 			return (free(var_tmp), ft_strlen(temp->env) - get_lenght(temp->env, '=') - 1);
// 		temp = temp->next;
// 	}
// 	// free(var_tmp);
// 	return (0);
// }

// char	*env_var_value(char *var_tmp, t_env *env_list)
// {
// 	t_env	*temp;

// 	temp = env_list;
// 	while (temp)
// 	{
// 		if (!ft_strncmp(temp->env, var_tmp, ft_strlen(var_tmp)) 
// 				&& ft_strlen(var_tmp) == get_lenght(temp->env, '='))
// 			return (printf("return = %s\n\n", temp->env + get_lenght(temp->env, '=') + 1), ft_strdup(temp->env + get_lenght(temp->env, '=') + 1));
// 		temp =temp->next;
// 	}
// 	// free(var_tmp);
// 	printf("testt avant return\n\n");
// 	return (NULL);
// }

// int	var_len(char *arg, int i, t_env *env_list)
// {
// 	(void)env_list;
// 	char	*var_tmp;

// 	var_tmp = malloc(sizeof(char) * get_lenght(arg + i, ' '));
// 	ft_strlcpy(var_tmp, arg + i + 1, get_lenght(arg + i, ' '));
// 	return (env_var_len(var_tmp, env_list));
// }

// char	*return_str(char *arg, int malloc_len, t_env *env_list)
// {
// 	char	*str;
// 	char	*temp_str;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	str = malloc(sizeof(char) * malloc_len);
// 	temp_str = malloc(sizeof(char) * malloc_len);
// 	while (arg[i])
// 	{
// 		while (arg[i] && arg[i] != '$')
// 		{
// 			str[j] = arg[i];
// 			i++;
// 			j++;
// 		}
// 		// str[j] = '\0';
// 		temp_str = str;
// 		printf("str = [%s]\n", str);
// 		printf("temp_str = [%s]\n", temp_str);
// 		printf("arg + i + 1 = [%s]\n", arg + i + 1);
// 		temp_str = ft_strjoin(temp_str, env_var_value(arg + i + 1, env_list));
// 		printf("temp_str = [%s]\n", temp_str);
// 		j = j + env_var_len(arg + i, env_list);
// 		while (arg[i] && arg[i] != ' ')
// 			i++;
// 	}
// 	free (str);
// 	return (temp_str);
// }

// char	*convert_env_var(char *arg, t_env *env_list)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		malloc_len;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] == '$')
// 		{
// 			j = j + var_len(arg, i, env_list);
// 			while (arg[i] && arg[i] != ' ')
// 			{
// 				i++;
// 				k++;
// 			}
// 		}
// 		if (arg[i])
// 			i++;
// 	}
// 	// if (j == 0)
// 	// 	return ();
// 	malloc_len = ft_strlen(arg) - k + j ;
// 	return (return_str(arg, malloc_len, env_list));	
// }

char	*get_checked_arg(t_parsed *p_list, t_env *env_list)
{
	if (p_list->token[0] == '\'')
		return (ft_strdup(p_list->token + 1));
	else if (p_list->token[0] == '\"')
		return (is_expand(p_list, env_list));
	else
		return (is_expand(p_list, env_list));
}


char	*is_expand(t_parsed *p_list, t_env *env_list)
{
	t_arg	*list;
	int		i;
	int		j;
	
	list = NULL;
	i = 0;
	while (p_list->token[i])
	{
		j = 0;
		while (p_list->token[i] && p_list->token[i] != '$')
		{
			my_lstadd_back_arg(&list, my_lstnew_arg(p_list->token[i]));
			i++;
		}
		if (!p_list->token[i])
			break ;
		i++;
		printf("p_list->token + i = %s\n", p_list->token + i);
		j = get_expand_value(p_list->token + i, list, env_list);
		while (j != 0)
		{
			i++;
			j--;
		}
		printf("--p_list->token[i] = %c\n", p_list->token[i]);
	}
	print_arg(list);
	return (p_list->token);
}

int	get_expand_value(char *str, t_arg *arg_list, t_env *env_list)
{
	t_env	*temp_e;
	int		i;
	int		len;

	i = 0;
	temp_e = env_list;
	while (temp_e)
	{
		len = is_permutable(str, temp_e->env);
		if (len > 0)
		{
			while (i < len)
			{
				// ici je recup pas la variable mis le nom de la variable
				my_lstadd_back_arg(&arg_list, my_lstnew_arg(temp_e->env[i]));
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
	if ((arg[i] == ' '|| arg[i] == '$') && env[i] == '=')
	{
		printf("arg[i] = %c\nenv[i] = %c\ni = %d\n", arg[i], env[i], i);
		return (i + 1);
	}
	return (0);
}



		// i = 0;


		
		// temp = malloc(sizeof(char) * (i + 1));
		// if (!temp)
		// 	return ;