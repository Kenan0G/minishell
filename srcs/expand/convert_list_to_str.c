/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:09:20 by kgezgin           #+#    #+#             */
/*   Updated: 2023/09/11 13:33:57 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*get_status_tab(t_arg *list, int tablen)
{
	t_arg	*temp;
	int		i;
	int		*tab;

	tab = malloc(sizeof(int) * tablen);
	if (!tab)
		return (NULL);
	temp = list;
	i = 0;
	tab_quote(i, tab, temp, tablen);
	return (tab);
}

void	tab_quote(int i, int *tab, t_arg *temp, int tablen)
{
	char	c;

	while (temp)
	{
		if (temp->c == '"' || temp->c == '\'')
		{
			c = simple_or_double(temp->c);
			tab[i] = 1;
			i++;
			temp = temp->next;
			while (temp && temp->c != c)
			{
				tab[i] = 0;
				i++;
				temp = temp->next;
			}
			if (i < tablen)
				tab[i] = 1;
		}
		else
			tab[i] = 0;
		i++;
		temp = temp->next;
	}
}

char	simple_or_double(char c)
{
	if (c == '\'')
		return ('\'');
	return ('"');
}

int	get_tab_len(t_arg *list)
{
	int		len;
	t_arg	*temp;

	len = 0;
	temp = list;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

int	str_malloc_len(int *tab, int tablen)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < tablen)
	{
		if (tab[i] == 0)
			len++;
		i++;
	}
	return (len);
}
