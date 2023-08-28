/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:54:30 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/28 12:31:51 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_env(t_env *env_list, char **env)
{
	t_env	*temp;
	int		i;

	if (!env || !env[0])
		return (printf("entrée dans en env_i\n"), env_i());
	temp = malloc(sizeof(t_env));
	if (!temp)
		return (NULL);
	i = 0;
	env_list = temp;
	while (env[i])
	{
		temp->env = NULL;
		temp->env = ft_strdup(env[i]);
		temp->printable = 1;
		if (!env[i + 1])
			temp->next = NULL;
		else
		{
			temp->next = malloc(sizeof(t_env));
			if (!temp->next)
				return (NULL);
			temp = temp->next;
		}
		i++;
	}
	return (env_list);
}

t_env	*env_i(void)
{
	t_env	*e_list;
	char	*pwd;
	char	*buf;

	buf = NULL;
	pwd = ft_strjoin("PWD=", getcwd(buf, 0));
	my_lstadd_back_env(&e_list, my_lstnew_env("OLDPWD", 0));
	my_lstadd_back_env(&e_list, my_lstnew_env(pwd, 1));
	my_lstadd_back_env(&e_list, my_lstnew_env("SHLVL=1", 1));
	my_lstadd_back_env(&e_list, my_lstnew_env("_=/usr/bin/env", 1));
	return (e_list);
}