/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:57:05 by red               #+#    #+#             */
/*   Updated: 2023/08/30 15:29:09 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    signal_ctrl_d(void)
{
    printf("exit \n");
    dprintf(1, "test\n");
    exit(0);
}

void    signal_ctrl_slash(int signo)
{
    (void)signo;
}

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
    else
    {
        // ft_putstr_fd("exit here doc \n", 2);
        in_here_doc = 0;
        write(2, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        // exit (100);
    }
    // if (signo == SIGINT) 
    // {
    //     rl_on_new_line();
    //     printf("\n");
    //     rl_replace_line("", 0);
    //     rl_redisplay();
    // }
}

void	ctrl_c_here(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	close(0);
}

// void	handle_sig(void)
// {
// 	if (in_here_doc= 1)
// 		signal(SIGINT, &signal_ctrl_c);
// 	else
// 	{
// 		signal(SIGINT, &ctrl_c);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// }

void    signal_ctrl_backslash(int signo)
{
    (void)signo;
}
