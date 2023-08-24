/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:11:54 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/24 19:11:38 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_pwd(t_cmd *c_list)
{
	char	*buf;
	char	*str;

	buf = NULL;
	if (c_list->arg[1] && c_list->arg[1][0] == '-' && c_list->arg[1][1] != '\0')
	{
		printf("pwd: %c%c: Invalid option\n", c_list->arg[1][0], c_list->arg[1][1]);
		return ;
	}
	str = getcwd(buf, 0);
	if (!str)
	{
		perror("pwd: error retrieving current directory: getcwd: cannot access parent directories");
		return ;
	}
	printf("%s\n", str);
	free(str);
}

t_env	*exec_cd(t_cmd *c_list, t_env *env_list, t_data *data)
{
	char	*buf;
	char	*oldpwd;

	buf = NULL;
	oldpwd = getcwd(buf, 0);
	if (nb_of_arg(c_list->arg) > 2)
		return (free(oldpwd), printf("cd: too many arguments\n"), env_list);
	if ((!c_list->arg[1] || c_list->arg[1][0] == '\0')
			|| (c_list->arg[1][0] == '~' && !c_list->arg[1][1]))
	{
		if (!cd_to_home(env_list))
			return (free(oldpwd), env_list);			
	}
	else if (c_list->arg[1][0] == '-' && c_list->arg[1][1] == '\0')
	{
		if (!cd_to_oldpwd(env_list, oldpwd))
			return (free(oldpwd), env_list);
	}
	else if (c_list->arg[1][0] == '-' && c_list->arg[1][1] != '\0')
	{
		printf("cd: %c%c: Invalid option\n", c_list->arg[1][0], c_list->arg[1][1]);
		return (free(oldpwd), env_list);	
	}
	else if (!oldpwd || chdir(c_list->arg[1]) == -1)
	{	
		perror(c_list->arg[1]);
		free(oldpwd);
		data->error_status = 1;
		return (env_list);
	}
	// if (oldpwd)
	update_pwd(oldpwd, env_list, NULL, data);
	if (oldpwd)
		free(oldpwd);
	return (env_list);
}

int	nb_of_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int	cd_to_oldpwd(t_env *env_list, char *oldpwd)
{
	t_env	*node;

	node = env_list;
	while (node && ft_strncmp(node->env, "OLDPWD=", 7))
		node = node->next;
	if (!node)
	{
		ft_putstr_fd("cd :OLDPWD not set\n", 2);
		return (0);	
	}
	if (!oldpwd || chdir(node->env+7) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(node->env+7);
		// ft_putstr_fd("cd : no such file or directory: ", 2);
		// ft_putstr_fd(node->env+7, 2);
		// ft_putstr_fd("\n", 2);
		return (0);
	}
	printf("%s\n", node->env+7);
	return (1);
}

int	cd_to_home(t_env *env_list)
{
	t_env	*node;

	node = env_list;
	while (node && ft_strncmp(node->env, "HOME=", 5))
		node = node->next;
	if (!node)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (0);
	}
	// printf("path = %s\n", node->env+5);
	if (chdir(node->env+5) == -1)
	{
		perror(node->env+5);
		// ft_putstr_fd("cd : no such file or directory: ", 2);
		// ft_putstr_fd(node->env+5, 2);
		// ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

t_env	*update_pwd(char *oldpwd, t_env *env_list, char  *buf, t_data *data)
{
	(void)data;
	int		i;
	char	*path;
	t_env	*temp;
	char	*pwd;

	i = 0;
	temp = env_list;
	if (!oldpwd)
	{
		oldpwd = ft_strdup(get_pwd(env_list));
		data->free_oldpwd = 1;
	}
	pwd = getcwd(buf, 0);
	while(temp && i < 2 )
	{
		if (!ft_strncmp(temp->env, "PWD=", 4))
		{
			free(temp->env);
			path = ft_strjoin("PWD=", pwd);
			temp->env = path;
			i++;
		}
		else if (!ft_strncmp(temp->env, "OLDPWD=", 7))
		{
			free(temp->env);
			if (oldpwd)
				path = ft_strjoin("OLDPWD=", oldpwd);
			else
				path = ft_strdup("OLDPWD=");
			temp->env = path;
			i++;
		}
		temp = temp->next;
	}
	if (pwd)
		free(pwd);
	if (data->free_oldpwd)
		free(oldpwd);
	return (env_list);
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