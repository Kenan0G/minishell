/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: red <red@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:27:17 by jsabound          #+#    #+#             */
/*   Updated: 2023/05/13 18:56:54 by red              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			if (p_list->status == COMMAND)
			{
				c_list->command = p_list->token;
				c_list->arg[i] = p_list->token;
				i++;
			}
			else if (p_list->status == ARG)
			{
				c_list->arg[i] = p_list->token;
				i++;
			}
			else if (p_list->status == LIMITER)
			{
				c_list->limiter[j] = p_list->token;
				j++;
			}
			c_list->limiter[j] = NULL;
			c_list->arg[i] = NULL;
			p_list = p_list->next;
		}
		if (p_list == NULL)
			break ;
		else
			p_list = p_list->next;
		c_list = c_list->next;
	}
}

t_cmd	*get_value(t_cmd *cmd_list, t_temp *parsed_list)
{
	int		i;
	int		j;
	t_cmd	*c_list;
	t_temp	*p_list;
	
	c_list = cmd_list;
	p_list = parsed_list;
	while (c_list)
	{
		i = 0;
		j = 0;
		while (p_list && p_list->status != PIPE)
		{
			if (p_list->status == ARG || p_list->status == COMMAND)
				i++;
			else if (p_list->status == HERE_DOC)
				j++;
			p_list = p_list->next;
		}
		c_list->nb_here_doc = j;
		c_list->here_doc_tmp = malloc(sizeof(char *) * (j + 1));
		c_list->limiter = malloc(sizeof(char *) * (j + 1));
		c_list->fd_here_doc = malloc(sizeof(int) * (j));
		c_list->arg = malloc(sizeof(char *) * (i + 1));
		if (p_list == NULL)
			break ;
		else
			p_list = p_list->next;
		c_list = c_list->next;
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
	// i = 0;
	// while (c_list->limiter[i])
	// {
	// 	printf("limiter[%d]  = %s\n", i, c_list->limiter[i]);
	// 	i++;
	// }
	while (c_list)
	{
		i = 0;
		while (i < c_list->nb_here_doc)
		{
			// printf("limiter = %s\n\n", c_list->limiter[i]);
			c_list->here_doc_tmp[i] = ft_strjoin(ft_strjoin(".here_doc_", ft_itoa(i + 1)), ".tmp");
			c_list->fd_here_doc[i] = here_doc(c_list->limiter[i], c_list->here_doc_tmp[i]);
			c_list->fd_here_doc[i] = open (c_list->here_doc_tmp[i], O_RDWR, 0644);
			i++;
		}
		c_list->here_doc_tmp[i] = NULL;
		// int j;
		// j = 0;
		// while (c_list->here_doc_tmp[j])
		// {
		// 	printf("here_doc.tmp %d = %s\nfd_here_doc %d = %d\n", j + 1, c_list->here_doc_tmp[j], j + 1, c_list->fd_here_doc[j]);
		// 	j++;
		// }
		c_list = c_list->next;
	}
}

t_cmd	*get_fd(t_cmd *cmd_list, t_temp *parsed_list)
{
	t_cmd	*c_list;
	t_temp	*p_list;
	int		i;
	int		j;
	
	p_list = parsed_list;
	c_list = cmd_list;
	// i = 0;
	get_here_doc(p_list, c_list);
	// int k = 0;
	// while (k < 2)
	// {
	// 	printf("fd %d = %d\n", k, c_list->fd_here_doc[k]);
	// 	k++;
	// }
	while (c_list)
	{
		i = 0;
		j = 0;
		while (p_list && p_list->status != PIPE)
		{
			if (i == 0 && p_list->status == FILE_IN)
			{
				// printf("test i\n");
				if (c_list->fd_in > 0)
					close(c_list->fd_in);
				c_list->fd_in = open(p_list->token, O_RDONLY);
				if (c_list->fd_in == -1)
				{
					perror(p_list->token);
					c_list->is_ok = 0;
	 				i = 1;
					// printf("test i_2\n");
				}
			}
			else if (i == 0 && p_list->status == HERE_DOC)
			{
				if (c_list->fd_in > 0)
					close(c_list->fd_in);
				c_list->fd_in = c_list->fd_here_doc[j];
				// printf("here_doc fd_in = %d\n", c_list->fd_in);
				j++;

			}
			else if (i == 0 && p_list->status == FILE_OUT)
			{	
				// printf("test j\n");
				if (c_list->fd_out > 0)
					close(c_list->fd_out);
				c_list->fd_out = open(p_list->token, O_WRONLY);
				if (c_list->fd_out == -1)
				{
					perror(p_list->token);
					c_list->is_ok = 0;
	 				i = 1;
				// 	printf("test j_2\n");
				}
			}
			p_list = p_list->next;
		}
		// printf("fd_in = %d\n\n", c_list->fd_in);
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
	cmd_list = get_fd(cmd_list, parsed_list);
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

