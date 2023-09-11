/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:42:04 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/11 18:13:23 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_end(t_cmd **c_list, t_parsed **p_list)
{
	ft_unlink(*c_list);
	ft_free_all(c_list, p_list);
}

void	ft_free_all(t_cmd **c_list, t_parsed **p_list)
{
	if (p_list)
		ft_free_p_list(p_list);
	if (c_list)
		ft_free_cmd_list(c_list);
}

int	ft_wait(t_data *data)
{
	int		i;
	int		j;
	int		exit_no;

	exit_no = 0;
	j = data->index;
	if (j == 0)
		j = j - 1;
	i = 0;
	while (i < j)
	{
		waitpid(data->pid[i], &exit_no, 0);
		if (WIFEXITED(exit_no))
			exit_no = WEXITSTATUS(exit_no);
		i++;
	}
	if (data->pid)
		free(data->pid);
	return (exit_no);
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
			i++;
		}
		temp = temp->next;
	}
}

void	ft_free_map(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	if (str)
		free(str);
}
