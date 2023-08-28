/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:17:50 by red               #+#    #+#             */
/*   Updated: 2023/08/28 15:42:52 by kgezgin          ###   ########.fr       */
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
