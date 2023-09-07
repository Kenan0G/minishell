/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:57:05 by red               #+#    #+#             */
/*   Updated: 2023/09/07 11:18:41 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    signal_ctrl_c(int signo)
{
    (void)signo;
    if (in_here_doc == 0)
    {        
        write(2, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    // else
    // {
    //     in_here_doc = 0;
    //     exit (-1);
    //     dprintf(2, "exit here_doc\n");
    //     write(2, "\n", 1);
    //     rl_replace_line("", 0);
    //     rl_on_new_line();
    //     rl_redisplay();
    // }
}

void    signal_ctrl_c_here_doc(int signo)
{
    (void)signo;
	t_here_doc *s;
    if (in_here_doc == 1)
    {
		s = starthd();
        in_here_doc = 0;
		close(s->fd);
		free(s->limiter);
		free(s->line);
        write(2, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        exit (130);
    }
}

void	signal_ctrl_c_in_child(int signo)
{
    (void)signo;
	exit (0);
}

void    signal_ctrl_slash(int signo)
{
    (void)signo;
}

void    signal_ctrl_backslash(int signo)
{
    (void)signo;
}

// void    signal_ctrl_d(void)
// {
//     printf("exit \n");
//     dprintf(1, "test\n");
//     exit(0);
// }