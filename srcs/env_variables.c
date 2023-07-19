/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:09:51 by kgezgin           #+#    #+#             */
/*   Updated: 2023/07/19 15:01:40 by kgezgin          ###   ########.fr       */
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



int	env_var_len(char *var_tmp, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->env, var_tmp, ft_strlen(var_tmp)) 
				&& ft_strlen(var_tmp) == get_lenght(temp->env, '='))
			return (free(var_tmp), ft_strlen(temp->env) - get_lenght(temp->env, '='));
	}
	// free(var_tmp);
	return (0);
}

char	*env_var_value(char *var_tmp, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->env, var_tmp, ft_strlen(var_tmp)) 
				&& ft_strlen(var_tmp) == get_lenght(temp->env, '='))
			return (free(var_tmp),temp->env + get_lenght(temp->env, '='));
	}
	free(var_tmp);
	return (0);
}

int	var_len(char *arg, int i, t_env *env_list)
{
	(void)env_list;
	char	*var_tmp;

	var_tmp = malloc(sizeof(char) * get_lenght(arg + i, ' '));
	ft_strlcpy(var_tmp, arg + i, get_lenght(arg + i, ' '));
	return (env_var_len(var_tmp, env_list));
}

char	*return_str(char *arg, int malloc_len, t_env *env_list)
{
	char	*str;
	char	*temp_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * malloc_len);
	temp_str = malloc(sizeof(char) * malloc_len);
	while (arg[i])
	{
		while (arg[i] && arg[i] != '$')
		{
			str[j] = arg[i];
			i++;
			j++;
		}
		temp_str = str;
		ft_strjoin(temp_str, env_var_value(arg + i, env_list));
		while (arg[i] && arg[i] != ' ')
			i++;
		j = j + env_var_len(arg + i, env_list);
	}
	dprintf(2, "str_final = [%s]\n", str);
	return (temp_str);
}

char	*convert_env_var(char *arg, t_env *env_list)
{
	int		i;
	int		j;
	int		malloc_len;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			j = j + var_len(arg, i, env_list);
			while (arg[i] && arg[i] != ' ')
				i++;
		}
		i++;
	}
	printf("avant if\n");
	if (j == 0)
		return(arg);
	printf("apres if\n");
	malloc_len = i + j;
	printf("malloc_len = %d\n", malloc_len);
	return_str(arg, malloc_len, env_list);
	return (NULL);
}

char	*get_env_var(char *arg, t_env *env_list)
{
	if (arg[0] == '\'')
		return (printf("test simple quote\n"), arg + 1);
	else
		return (printf("test else\n"), convert_env_var(arg, env_list));
}

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	t_env	*env_list;
// 	env_list = NULL;
// 	env_list = get_env(env_list, env);
// 	char *str = get_env_var(av[1], env_list);
// 	printf("[%s]\n", str);
// 	return (0);
// }