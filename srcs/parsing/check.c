/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:17:50 by red               #+#    #+#             */
/*   Updated: 2023/08/30 15:51:13 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// echo hola >>> bonjour
// invalid read chevron in  ---> test effectué : cat <<
// invalid read chevron out ---> test effectué : cat <<

// cat << |
// poour ce test tu dois check si apres un heredoc ya un pipe ou pas essaye de 

// echo " sdv'sqdf"
// faut pas check la simple quote pcke elle est deja dans des double quote
// actuellement ton code retourne une erreur mais ca doit pas faire d'erreur et le echo doit afficher :
// $>  sdv'sqdf
// mais du coup c la meme dans l'autre sens si ya nombre impaire de double quote entre deux simple quote faut pas retourner d'erreur

/*
modifs_minishell git:(master) ✗ valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=valgrind.txt ./minishell
==1802== Memcheck, a memory error detector
==1802== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1802== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==1802== Command: ./minishell
==1802==
==1802== error calling PR_SET_PTRACER, vgdb might block
minishell$> cat << l
> ^C
line =
return test
==1812==
==1812== FILE DESCRIPTORS: 3 open (3 std) at exit.
==1812==
==1812== HEAP SUMMARY:
==1812==     in use at exit: 208,215 bytes in 227 blocks
==1812==   total heap usage: 527 allocs, 300 frees, 241,611 bytes allocated
==1812==
==1812== LEAK SUMMARY:
==1812==    definitely lost: 0 bytes in 0 blocks
==1812==    indirectly lost: 0 bytes in 0 blocks
==1812==      possibly lost: 0 bytes in 0 blocks
==1812==    still reachable: 0 bytes in 0 blocks
==1812==         suppressed: 208,215 bytes in 227 blocks
==1812==
==1812== For lists of detected and suppressed errors, rerun with: -s
==1812== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 1 from 1)
minishell$>
==1802== Invalid read of size 1
==1802==    at 0x10EF28: check_between_pipe (check.c:163)
==1802==    by 0x10EE3B: check_pipe (check.c:141)
==1802==    by 0x10EB2F: check (check.c:33)
==1802==    by 0x109591: main (minishell.c:44)
==1802==  Address 0x4b53d81 is 0 bytes after a block of size 1 alloc'd
==1802==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1802==    by 0x4899BAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x4877694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x4881D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x10955E: main (minishell.c:40)
==1802==
==1802== Invalid read of size 1
==1802==    at 0x10EF50: check_between_pipe (check.c:165)
==1802==    by 0x10EE3B: check_pipe (check.c:141)
==1802==    by 0x10EB2F: check (check.c:33)
==1802==    by 0x109591: main (minishell.c:44)
==1802==  Address 0x4b53d81 is 0 bytes after a block of size 1 alloc'd
==1802==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1802==    by 0x4899BAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x4877694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x4881D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x10955E: main (minishell.c:40)
==1802==
==1802== Invalid read of size 1
==1802==    at 0x10F39A: check_first_char (check.c:240)
==1802==    by 0x10EB40: check (check.c:34)
==1802==    by 0x109591: main (minishell.c:44)
==1802==  Address 0x4b53d7f is 1 bytes before a block of size 1 alloc'd
==1802==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1802==    by 0x4899BAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x4877694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x4881D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x10955E: main (minishell.c:40)
==1802==
==1802== Invalid read of size 1
==1802==    at 0x10F3B8: check_first_char (check.c:240)
==1802==    by 0x10EB40: check (check.c:34)
==1802==    by 0x109591: main (minishell.c:44)
==1802==  Address 0x4b53d7f is 1 bytes before a block of size 1 alloc'd
==1802==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1802==    by 0x4899BAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x4877694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x4881D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==1802==    by 0x10955E: main (minishell.c:40)
==1802==
minishell$>
*/

int check(char *str)
{
    if (check_metacaractere(str) == 2 || check_double_quote(str) == 2
			|| check_simple_quote(str) == 2 || check_pipe(str) == 2
			|| check_first_char(str) == 2)
		return (2);
	else
		return (0);
}

int check_double_quote(char *str)
{
    int i;
    int res;

    i = 0;
    res = 0;
    while (str[i])
    {
        if (str[i] == '"')
            res++;
        i++;
    }
    if (res % 2)
    {
        printf("minishell : missing double quote\n");
        return (2);
    }
	return (0);
}

int check_simple_quote(char *str)
{
    int i;
    int res;

    i = 0;
    res = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            res++;
        i++;
    }
    if (res % 2)
    {
        printf("minishell : missing simple quote\n");
        return (2);
    }
	return (0);
}

int check_metacaractere(char *str)
{
    if (str[0] == ')')
    {
        printf("minishell: syntax error near unexpected token `)'\n");
        return (2);
    }
    else if (str[0] == '(')
    {
        printf("minishell: syntax error near unexpected token `('\n");
        return (2);
    }
    else if (check_metacaractere2(str) == 2)
		return (2);
	else
		return (0);
}

int check_metacaractere2(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '&' && str[i + 1] == '&')
        {
            printf("minishell: syntax error near unexpected token `&&'\n");
            return (2);
        }
        else if (str[i] == ';' && str[i + 1] == ';')
        {
            printf("minishell: syntax error near unexpected token `;;'\n");
            return (2);
        }
        else if (str[i] == ';' && str[i + 1] != ';')
        {
            printf("minishell: syntax error near unexpected token `;'\n");
            return (2);
        }
        else if (str[i] == '&' && str[i + 1] != '&')
        {
            printf("minishell: syntax error near unexpected token `&'\n");
            return (2);
        }
        i++;
    }
	return (0);
}

int check_pipe(char *str)
{
    int i;

    if (str[0] == '|')
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        return (2);
    }
    else if (check_between_pipe(str) == 2)
		return (2);
    i = 0;
    while (str[i] != '|' && str[i])
    {
        if ((str[i + 1] == '|' && str[i] == '>') || (str[i + 1] == '|' && str[i] == '<'))
        {
            printf("minishell: syntax error near unexpected token `|'\n");
            return (2);
        }
        i++;
    }
	return (0);
}

int check_between_pipe(char *str)
{
    int i;
    int x;

    x = 0;
    i = 1;
    while (str[i] && str[i] != '|')
        i++;
    if (!str[i] || !str[i + 1])
        return (0);
    i++;
    while (str[i] != '|' && str[i])
    {
        if (str[i] != ' ' && str[i] != '\t')
            x++;
        i++;
    }
    if (!x)
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        return (2);
    }
	return (0);
}

int check_chevron_out(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] == '>' && str[i + 1] == '>' && str[i + 3] == '>') || (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'))
        {
            printf("minishell: syntax error near unexpected token `>>'\n");
            return (2);
        }
        else if ((str[i] == '>' && str[i + 2] == '>') || (str[i] == '<' && str[i + 2] == '>'))
        {
            printf("minishell: syntax error near unexpected token `>'\n");
            return (2);
        }
        i++;
    }
	return (0);
}

int check_chevron_in(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<') || (str[i] == '<' && str[i + 1] == '<' && str[i + 3] == '<'))
        {
            printf("minishell: syntax error near unexpected token `<<'\n");
            return (2);
        }
        else if ((str[i] == '<' && str[i + 2] == '<') || (str[i] == '>' && str[i + 2] == '<'))
        {
            printf("minishell: syntax error near unexpected token `<'\n");
            return (2);
        }
        i++;
    }
	return (0);
}

int check_first_char(char *str)
{
    if ((str[0] == '>' && !str[1]) || (str[0] == '<' && !str[1]) || (str[0] == '>' && str[1] == '>' && !str[2]) || (str[0] == '<' && str[1] == '<' && !str[2]) || (str[0] == '<' && str[1] == '>'))
    {
        printf("minishell: syntax error near unexpected token `newline'\n");
        return (2);
    }
	else
	{
		if (check_chevron_in(str) == 2)
			return (2);
		if (check_chevron_out(str) == 2)
			return (2);
	}
    if (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<')
    {
        printf("minishell: syntax error near unexpected token `newline'\n");
        return (2);
    }
	return (0);
}
