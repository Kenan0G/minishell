/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:27:17 by jsabound          #+#    #+#             */
/*   Updated: 2023/06/22 17:36:41 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_args_utils(t_cmd *c_list, t_temp *p_list, int *i, int *j)
{
	if (p_list->status == COMMAND)
	{
		c_list->command = p_list->token;
		c_list->arg[*i] = p_list->token;
		(*i)++;
	}
	else if (p_list->status == ARG)
	{
		c_list->arg[*i] = p_list->token;
		(*i)++;
	}
	else if (p_list->status == LIMITER)
	{
		c_list->limiter[*j] = p_list->token;
		(*j)++;
	}
	c_list->limiter[*j] = NULL;
	c_list->arg[*i] = NULL;
}

void	get_args(t_cmd *cmd_list, t_temp *parsed_list)
{
	int		i;
	int		j;
	t_cmd	*c_list;
	t_temp	*p_list;
	
	c_list = cmd_list;
	p_list = parsed_list;
	while(c_list)
	{
		i = 0;
		j = 0;
		while (p_list && p_list->status != PIPE)
		{
			get_args_utils(c_list, p_list, &i, &j);
			p_list = p_list->next;
			// printf("j = %d\n", j);
			// printf("i = %d\n", i);
		}
		if (p_list == NULL)
			break ;
		else
			p_list = p_list->next;
		c_list = c_list->next;
	}
}

void	get_value_malloc(t_cmd *c_list, int i, int j)
{
	// printf("MALLOC ======== i = %d\n", i);
	// printf("MALLOC ======== j = %d\n", j);
	// printf("-------------------------------------\n");
	c_list->nb_here_doc = j;
	c_list->here_doc_tmp = malloc(sizeof(char *) * (j + 1));
	c_list->limiter = malloc(sizeof(char *) * (j + 1));
	c_list->fd_here_doc = malloc(sizeof(int) * (j));
	c_list->arg = malloc(sizeof(char *) * (i + 1));
}

t_temp	*get_value_i_j(t_temp *p_list, int *i, int *j)
{
	while (p_list && p_list->status != PIPE)
	{
		// printf("p_list->status = %d\n", p_list->status);
		// printf("p_list->token = %s\n", p_list->token);
		// printf("\n");
		if (p_list->status == ARG || p_list->status == COMMAND)
		{
			// printf("if i\n");
			*i = (*i)+ 1;
		}
		else if (p_list->status == HERE_DOC)
		{
			// printf("if j\n");
			*j = (*j)+ 1;
		}
		p_list = p_list->next;
	}
	return (p_list);
}

t_cmd	*get_value(t_cmd *cmd_list, t_temp *parsed_list)
{
	int		i;
	int		j;
	t_cmd	*c_list;
	t_temp	*p_list;
	
	c_list = cmd_list;
	p_list = parsed_list;
	int k = 0;
	while (c_list)
	{
		i = 0;
		j = 0;
		p_list = get_value_i_j(p_list, &i, &j);
		get_value_malloc(c_list, i, j);

		if (p_list == NULL)
			break ;
		else
			p_list = p_list->next;
		c_list = c_list->next;
		k++;
	}
	get_args(cmd_list, parsed_list);
	return (cmd_list);
}


void	get_here_doc(t_temp *p_list, t_cmd *cmd_list)
{
	int		i;
	t_cmd	*c_list;

	(void)p_list;
	c_list = cmd_list;
	while (c_list)
	{
		i = 0;
		while (i < c_list->nb_here_doc)
		{
			c_list->here_doc_tmp[i] = ft_strjoin(ft_strjoin(".here_doc_", ft_itoa(i + 1)), ".tmp");
			c_list->fd_here_doc[i] = here_doc(c_list->limiter[i], c_list->here_doc_tmp[i]);
			c_list->fd_here_doc[i] = open (c_list->here_doc_tmp[i], O_RDWR, 0644);
			if (c_list->fd_here_doc[i] <= 0)
			{
				perror(c_list->here_doc_tmp[i]);
			}
			i++;
		}
		c_list->here_doc_tmp[i] = NULL;
		c_list = c_list->next;
	}
}

t_cmd	*get_fd(t_cmd *cmd_list, t_temp *parsed_list, t_data *data)
{
	t_cmd	*c_list;
	t_temp	*p_list;
	
	p_list = parsed_list;
	c_list = cmd_list;
	get_here_doc(p_list, c_list);
	while (c_list)
	{
		data->i = 0;
		data->j = 0;
		while (p_list && p_list->status != PIPE)
		{
			if (data->i == 0 && p_list->status == FILE_IN)
			{
				if (c_list->fd_in > 0)
					close(c_list->fd_in);
				c_list->fd_in = open(p_list->token, O_RDONLY);
				if (c_list->fd_in == -1)
				{
					perror(p_list->token);
					c_list->is_ok = 0;
	 				data->i = 1;
				}
			}
			else if (data->i == 0 && p_list->status == HERE_DOC)
			{
				if (c_list->fd_in > 0)
					close(c_list->fd_in);
				printf("data->j == %d\n\n\n", data->j);
				c_list->fd_in = c_list->fd_here_doc[data->j];
				data->j++;

			}
			else if (data->i == 0 && p_list->status == REDIR_OUT)
			{	
				if (c_list->fd_out > 0)
					close(c_list->fd_out);
				c_list->fd_out = open(p_list->next->token, O_WRONLY | O_TRUNC | O_CREAT, 0777);
				if (c_list->fd_out == -1)
				{
					perror(p_list->next->token);
					c_list->is_ok = 0;
	 				data->i = 1;
				}
			}
			else if (data->i == 0 && p_list->status == APPEND)
			{
				if (c_list->fd_out > 0)
					close(c_list->fd_out);
				c_list->fd_out = open(p_list->next->token, O_WRONLY | O_APPEND | O_CREAT, 0777);
				if (c_list->fd_out == -1)
				{
					perror(p_list->next->token);
					c_list->is_ok = 0;
	 				data->i = 1;
				}
			}
			p_list = p_list->next;
		}
		if (p_list == NULL)
			break ;
		else
			p_list = p_list->next;
		c_list = c_list->next;
	}
	return (cmd_list);
}

t_cmd	*create_cmd_list(t_temp *parsed_list, t_data *data)
{
	t_cmd	*cmd_list;
	int		i;

	i = 0;
	cmd_list = NULL;
	while (i != data->cmd_count)
	{
		my_lstadd_back_cmd(&cmd_list, my_lstnew_cmd());
		i++;
	}
	cmd_list = get_value(cmd_list, parsed_list);
	cmd_list = get_fd(cmd_list, parsed_list, data);
	return (cmd_list);
}

void	my_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{	
	t_cmd	*current_node;

	current_node = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new;
}

t_cmd	*my_lstnew_cmd()
{
	t_cmd	*liste;

	liste = malloc(sizeof(*liste));
	liste->next = NULL;
	liste->fd_in = 0;
	liste->fd_out = 0;
	liste->is_ok = 1;
	return (liste);
}

void	init_data(t_data *data, char **env)
{
	ft_memset(data, 0, sizeof(t_data));
	data->cmd_count = 0;
	data->env = env;
	data->i = 0;
	data->j = 0;
}

// int main (int ac, char **av, char **env)
// {
// 	t_cmd			*cmd_list;
// 	t_temp			*token;
// 	t_data			data;
// 	// char			*str;

// 	// (void)env;
// 	(void)ac;
// 	// (void)av;
// 	// while (1)
// 	// {
// 	// 	str = readline("minishell$> ");
// 	// 	add_history(str);
// 	// }
// 	init_data(&data, env);
// 	token = temp_list(&data, av);
// 	cmd_list = create_cmd_list(token, &data);
// 	(void)cmd_list;
// 	return (0);
// }

// void	fd_file_in(t_temp *p_list, t_cmd *c_list, t_data *data)
// {
// 	if (c_list->fd_in > 0)
// 		close(c_list->fd_in);
// 	c_list->fd_in = open(p_list->token, O_RDONLY);
// 	if (c_list->fd_in == -1)
// 	{
// 		perror(p_list->token);
// 		c_list->is_ok = 0;
// 		data->i = 1;
// 	}
// }

// void	fd_here_doc(t_cmd *c_list, t_data *data)
// {
// 	if (c_list->fd_in > 0)
// 		close(c_list->fd_in);
// 	c_list->fd_in = c_list->fd_here_doc[data->j];
// 	data->j++;
// }

// void	fd_file_out(t_temp *p_list, t_cmd *c_list, t_data *data, int is_append)
// {
// 	if (is_append)
// 	{
// 		if (c_list->fd_out > 0)
// 			close(c_list->fd_out);
// 		c_list->fd_out = open(p_list->next->token, O_WRONLY | O_APPEND | O_CREAT, 0777);
// 		if (c_list->fd_out == -1)
// 		{
// 			perror(p_list->next->token);
// 			c_list->is_ok = 0;
// 			data->i = 1;
// 		}
// 	}
// 	else
// 	{
// 		if (c_list->fd_out > 0)
// 			close(c_list->fd_out);
// 		c_list->fd_out = open(p_list->next->token, O_WRONLY | O_TRUNC | O_CREAT, 0777);
// 		if (c_list->fd_out == -1)
// 		{
// 			perror(p_list->next->token);
// 			c_list->is_ok = 0;
// 			data->i = 1;
// 		}
// 	}
// }

// void	ft_open(t_temp *p_list, t_cmd *c_list, t_data *data)
// {
// 	if (data->i == 0 && p_list->status == FILE_IN)
// 		fd_file_in(p_list, c_list, data);
// 	else if (data->i == 0 && p_list->status == HERE_DOC)
// 		fd_here_doc(c_list, data);
// 	else if (data->i == 0 && p_list->status == REDIR_OUT)
// 		fd_file_out(p_list, c_list, data, 0);
// 	else if (data->i == 0 && p_list->status == APPEND)
// 		fd_file_out(p_list, c_list, data, 1);
// }

// t_cmd	*get_fd(t_cmd *cmd_list, t_temp *parsed_list, t_data *data)
// {
// 	t_cmd	*c_list;
// 	t_temp	*p_list;
	
// 	p_list = parsed_list;
// 	c_list = cmd_list;
// 	get_here_doc(p_list, c_list);
// 	while (c_list)
// 	{
// 		printf("\ntest\n");
// 		while (p_list && p_list->status != PIPE)
// 		{
// 			printf("test---------2\n");
// 			ft_open(p_list, c_list, data);
// 			p_list = p_list->next;
// 		}
// 		printf("test---------3\n");
// 		if (p_list == NULL)
// 		{
// 			printf("test---------4\n");
// 			break ;
// 		}
// 		else
// 			p_list = p_list->next;
// 		c_list = c_list->next;
// 	}
// 	return (cmd_list);
// }