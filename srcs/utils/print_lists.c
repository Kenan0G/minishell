/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:30:20 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/12 20:17:20 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	print_list(t_parsed *token)
// {
// 	t_parsed	*temp;

// 	temp = token;
// 	while (temp)
// 	{
// 		printf("str =		%s\n", temp->token);
// 		printf("status =	%d\n\n", temp->status);
// 		temp = temp->next;
// 	}
// }

// void	print_arg(t_arg *token)
// {
// 	t_arg	*temp;

// 	temp = token;
// 	while (temp)
// 	{
// 		printf("[%c]", temp->c);
// 		temp = temp->next;
// 	}
// 	printf("\n");
// }

// void	print_cmd_list(t_cmd *token)
// {
// 	int i;
// 	t_cmd *temp;

// 	temp = token;
// 	while (temp)
// 	{
// 		i = 0;
// 		while (temp->arg[i])
// 		{
// 			printf("arg[%d]  = %s\n", i, temp->arg[i]);
// 			i++;
// 		}
// 		i = 0;
// 		while (temp->limiter[i])
// 		{
// 			printf("limiter[%d]  = %s\n", i, temp->limiter[i]);
// 			i++;
// 		}
// 		i = 0;
// 		while (i < token->nb_here_doc)
// 		{
// 			printf("temp->hd_fd[i] = %d\n", temp->hd_fd[i]);
// 			i++;
// 		}
// 		i = 0;
// 		while (temp->hd_file[i])
// 		{
// 			printf("temp->hd_file[i] = %s\n", temp->hd_file[i]);
// 			i++;
// 		}
// 		printf("command = %s\n", temp->command);
// 		printf("fd_in   = %d\n", temp->fd_in);
// 		printf("fd_out  = %d\n\n", temp->fd_out);
// 		temp = temp->next;
// 	}
// }