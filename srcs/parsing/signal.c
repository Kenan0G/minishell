/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:57:05 by red               #+#    #+#             */
/*   Updated: 2023/09/01 17:27:29 by kgezgin          ###   ########.fr       */
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
    else
    {
        in_here_doc = 0;
        write(2, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        exit (-1);
    }
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