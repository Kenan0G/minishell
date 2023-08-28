/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:14:24 by kgezgin           #+#    #+#             */
/*   Updated: 2023/05/10 15:33:15 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"


/*
void	ft_close(t_data *data)
{
	if (data->fd_infile)
		close(data->fd_infile);
	if (data->fd_outfile)
		close(data->fd_outfile);
	if (data->fd_pipe[0])
		close(data->fd_pipe[0]);
	if (data->fd_pipe[1])
		close(data->fd_pipe[1]);
	if (data->fd_temp)
		close(data->fd_temp);
}

void	ft_wait(t_data *data, int ac)
{
	(void)ac;
	while (data->index-- > 0)
		waitpid(data->pid[data->index], NULL, 0);
	free(data->pid);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

*/