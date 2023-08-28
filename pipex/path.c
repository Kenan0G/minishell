/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:16:17 by kgezgin           #+#    #+#             */
/*   Updated: 2023/05/10 15:32:24 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/*
void	get_path(char **envp, t_data *data)
{
	int	i;

	i = data->index + 2 + data->here_doc;
	ft_path(envp, data);
	data->cmd = ft_split(data->av[i], ' ');
	if (is_path(data->av[i]) == 0)
		data->path = path_check(data);
	else
		data->path = ft_strdup(data->av[i]);
	if (data->path_begining)
		ft_free_map(data->path_begining);
}

int	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*path_check(t_data *data, t_cmd *list)
{
	char	*good_path;
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	// if (!data->cmd[0] || !data->cmd[0][0])
	// {
	// 	ft_putstr_fd("Command '' not found\n", 2);
	// 	ft_error(data, 127);
	// }
	str = list->command;
	temp = ft_strjoin("/", str);
	while (data->path_begining && data->path_begining[i])
	{
		good_path = ft_strjoin(data->path_begining[i], temp);
		if (access(good_path, X_OK) == 0)
			return (free(temp), good_path);
		free(good_path);
		i++;
	}
	ft_error_path(data, temp, list);
	// ft_error(data, errno);
	return (NULL);
}

void	ft_error_path(t_data *data, char *temp, t_cmd *list)
{
	char	*str;
	char	*str_2;

	free(temp);
	str = ft_strjoin("Command '", list->command);
	str_2 = ft_strjoin(str, "' not found \n");
	write(2, str_2, ft_strlen(str_2));
	free(str);
	free(str_2);
	// ft_close(data);
}

void	ft_path(char **envp, t_data *data)
{
	int		i;

	i = 0;
	while (envp && envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp && !envp[i])
		return ;
	data->path_begining = ft_split(envp[i] + 5, ':');
}
*/