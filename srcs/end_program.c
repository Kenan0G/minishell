/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:42:04 by kgezgin           #+#    #+#             */
/*   Updated: 2023/06/23 18:42:32 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_wait(t_data *data)
{
	while (data->index-- > 0)
		waitpid(data->pid[data->index], NULL, 0);
	free(data->pid);
}

void	ft_unlink(t_cmd *list)
{
	t_cmd	*temp;
	int		i;

	temp = list;
	while (temp)
	{
		i = 0;
		while (temp->hd_file[i])
		{
			unlink (temp->hd_file[i]);
			free (temp->hd_file[i]);
			free (temp->limiter[i]);
			i++;
		}
		free(temp->hd_file);
		free (temp->limiter);
		temp = temp->next;
	}
}

void	ft_free_list(t_cmd **lst)
{
	t_cmd	*temp;
	t_cmd	*tmp2;

	temp = (*lst);
	while (temp)
	{
		tmp2 = temp->next;
		free(temp);
		temp = tmp2;
	}
}