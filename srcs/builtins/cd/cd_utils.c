/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:58:36 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/08 16:19:36 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*update_pwd(char *oldpwd, t_env *env_list, char *buf, t_data *data)
{
	char	*path;
	char	*pwd;

	path = NULL;
	if (!oldpwd)
	{
		oldpwd = ft_strdup(get_pwd(env_list));
		data->free_oldpwd = 1;
	}
	pwd = getcwd(buf, 0);
	update_cd_utils(env_list, pwd, oldpwd, path);
	if (pwd)
		free(pwd);
	if (data->free_oldpwd)
		free(oldpwd);
	return (env_list);
}

void	update_cd_utils(t_env *temp, char *pwd, char *oldpwd, char *path)
{
	int	i;

	i = 0;
	while (temp && i < 2)
	{
		if (!ft_strncmp(temp->env, "PWD", 3))
		{
			free(temp->env);
			path = ft_strjoin("PWD=", pwd);
			temp->env = path;
			i++;
		}
		else if (!ft_strncmp(temp->env, "OLDPWD", 6))
		{
			free(temp->env);
			if (oldpwd)
				path = ft_strjoin("OLDPWD=", oldpwd);
			else
				path = ft_strdup("OLDPWD=");
			temp->printable = 1;
			temp->env = path;
			i++;
		}
		temp = temp->next;
	}
}

char	*get_pwd(t_env *env_list)
{
	t_env	*node;

	node = env_list;
	while (node && ft_strncmp(node->env, "PWD=", 4))
		node = node->next;
	if (!node)
		return (NULL);
	return (node->env + 4);
}
