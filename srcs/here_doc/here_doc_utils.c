/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:13:14 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/11 15:13:24 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	generate_hd_file_name(t_cmd *c_list, int i)
{
	char	*file_no;
	char	*file_temp_name;

	file_no = ft_itoa(i + 1);
	file_temp_name = ft_strjoin(".here_doc_", file_no);
	c_list->hd_file[i] = ft_strjoin(file_temp_name, ".tmp");
	free(file_no);
	free(file_temp_name);
}

void	*starthd(void)
{
	static t_here_doc	var = {0};

	return (&var);
}

void	ft_close(t_cmd *c_list, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (c_list->hd_fd[j] > 0)
			close(c_list->hd_fd[j]);
		j++;
	}
}

int	open_here_doc(char *path)
{
	int		fd;

	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(path);
		exit (EXIT_FAILURE);
	}
	return (fd);
}
