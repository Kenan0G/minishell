/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:11:54 by kgezgin           #+#    #+#             */
/*   Updated: 2023/08/23 18:01:02 by kgezgin          ###   ########.fr       */
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
	printf("%s\n", str);
	free(str);
}

t_env	*exec_cd(t_cmd *c_list, t_env *env_list)
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
		if (!cd_to_oldpwd(env_list))
			return (free(oldpwd), env_list);
	}
	else if (c_list->arg[1][0] == '-' && c_list->arg[1][1] != '\0')
	{
		printf("cd: %c%c: Invalid option\n", c_list->arg[1][0], c_list->arg[1][1]);
		return (free(oldpwd), env_list);	
	}
	else if (chdir(c_list->arg[1]) == -1)
	{
		ft_putstr_fd("cd : no such file or directory: ", 2);
		ft_putstr_fd(c_list->arg[1], 2);
		ft_putstr_fd("\n", 2);
		free(oldpwd);
		return (env_list);
	}
	update_pwd(oldpwd, env_list, NULL);
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

int	cd_to_oldpwd(t_env *env_list)
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
	printf("%s\n", node->env+7);
	if (chdir(node->env+7) == -1)
	{
		ft_putstr_fd("cd : no such file or directory: ", 2);
		ft_putstr_fd(node->env+7, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
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
		ft_putstr_fd("cd : no such file or directory: ", 2);
		ft_putstr_fd(node->env+5, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

t_env	*update_pwd(char *oldpwd, t_env *env_list, char  *buf)
{
	int		i;
	char	*path;
	t_env	*temp;
	char	*pwd;

	i = 0;
	temp = env_list;
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
			path = ft_strjoin("OLDPWD=", oldpwd);
			temp->env = path;
			i++;
		}
		temp = temp->next;
	}
	free(pwd);
	return (env_list);
}
