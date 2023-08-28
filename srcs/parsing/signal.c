/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:57:05 by red               #+#    #+#             */
/*   Updated: 2023/08/28 18:48:51 by kgezgin          ###   ########.fr       */
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
    write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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
// 	if (sig = 1)
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
