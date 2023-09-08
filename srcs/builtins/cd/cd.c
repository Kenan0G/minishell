/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:11:54 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/08 15:05:27 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	else if (c_list->arg[1][0] == '-')
		return (printf("cd: %c%c: Invalid option\n",
				c_list->arg[1][0], c_list->arg[1][1]), free(oldpwd), env_list);
	else if (!oldpwd || chdir(c_list->arg[1]) == -1)
		return (cd_utils(c_list, data, oldpwd), env_list);
	update_pwd(oldpwd, env_list, NULL, data);
	if (oldpwd)
		free(oldpwd);
	return (env_list);
}

void	cd_utils(t_cmd *c_list, t_data *data, char *oldpwd)
{
	ft_putstr_fd("cd: ", 2);
	perror(c_list->arg[1]);
	free(oldpwd);
	data->error_status = 1;
}

int	nb_of_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
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
	if (chdir(node->env + 5) == -1)
	{
		perror(node->env + 5);
		return (0);
	}
	return (1);
}
