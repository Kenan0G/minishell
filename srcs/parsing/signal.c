/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: red <red@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:57:05 by red               #+#    #+#             */
/*   Updated: 2023/08/27 09:59:46 by red              ###   ########.fr       */
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
    if (signo == SIGINT) 
    {
        rl_on_new_line();
        printf("\n");
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    signal_ctrl_backslash(int signo)
{
    (void)signo;
}
