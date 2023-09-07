/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:57:05 by red               #+#    #+#             */
/*   Updated: 2023/09/07 15:01:36 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    signal_ctrl_c(int signo)
{
    (void)signo;
    if (g_in_here_doc == 0)
    {        
        write(2, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    // else
    // {
    //     g_in_here_doc = 0;
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
    if (g_in_here_doc == 1)
    {
		s = starthd();
        g_in_here_doc = 0;
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