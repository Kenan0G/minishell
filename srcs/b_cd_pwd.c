/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:11:54 by kgezgin           #+#    #+#             */
/*   Updated: 2023/07/18 13:17:12 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_pwd(t_cmd *c_list, t_parsed *p_list, t_data *data)
{
	char	*buf;
	char	*str;

	buf = NULL;
	str = getcwd(buf, 0);
	printf("%s\n", str);
	free(data->pid);
	ft_free_all(&c_list, &p_list, data, NULL);
}

t_env	*exec_cd(t_cmd *c_list, t_env *env_list)
{
	char	*buf;
	char	*oldpwd;

	buf = NULL;
	oldpwd = getcwd(buf, 0);
	if (chdir(c_list->arg[1]) == -1)
	{
		ft_putstr_fd("cd : no such file or directory: ", 2);
		ft_putstr_fd(c_list->arg[1], 2);
		ft_putstr_fd("\n", 2);
		return (env_list);
	}
	update_pwd(oldpwd, env_list, NULL);
	return (env_list);
}

t_env	*update_pwd(char *oldpwd, t_env *env_list, char  *buf)
{
	int		i;
	char	*path;
	t_env	*temp;
	
	i = 0;
	temp = env_list;
	while(temp && i < 2 )
	{
		if (!ft_strncmp(temp->env, "PWD=", 4))
		{
			free(temp->env);
			path = ft_strjoin("PWD=", getcwd(buf, 0));
			temp->env = path;
			i++;
		}
		else if (!ft_strncmp(temp->env, "OLDPWD=", 7))
		{
			free(temp->env);
			path = ft_strjoin("OLDPWD=", oldpwd);
			temp->env = path;
			i++;
		}
		temp = temp->next;
	}
	return (env_list);
}