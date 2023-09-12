/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:30:52 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 16:03:28 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_directory(char *str)
{
	int	fd;

	fd = open(str, __O_DIRECTORY);
	if (fd > 0)
	{
		printf("%s: is a directory\n", str);
		if (fd > 0)
			close(fd);
		return (2);
	}
	if (fd > 0)
		close(fd);
	return (1);
}

int	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			return (check_directory(str));
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
	if (list->command[0] == '\0')
		return (ft_error_path(NULL, list), NULL);
	str = list->command;
	temp = ft_strjoin("/", str);
	while (data->path_begining && data->path_begining[i])
	{
		good_path = ft_strjoin(data->path_begining[i], temp);
		if (access(good_path, X_OK | F_OK) != -1)
			return (free(temp), good_path);
		if (good_path)
			free(good_path);
		i++;
	}
	ft_error_path(temp, list);
	return (NULL);
}

void	ft_error_path(char *temp, t_cmd *list)
{
	char	*str;
	char	*str_2;

	if (temp)
		free(temp);
	str = ft_strjoin("Command '", list->command);
	str_2 = ft_strjoin(str, "' not found \n");
	write(2, str_2, ft_strlen(str_2));
	free(str);
	free(str_2);
}

void	ft_path(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (envp && envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp && !envp[i])
	{
		if (envp)
			ft_free_map(envp);
		return ;
	}
	data->path_begining = ft_split(envp[i] + 5, ':');
	if (envp)
		ft_free_map(envp);
}
