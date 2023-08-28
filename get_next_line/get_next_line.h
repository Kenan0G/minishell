/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:52:48 by kgezgin           #+#    #+#             */
/*   Updated: 2023/04/25 17:18:15 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

char	*get_next_line(int fd, int c);
size_t	my_strlen(char *str);
char	*my_strjoin(char *s1, char *s2);
void	*my_calloc(size_t count, size_t size);
char	*my_strchr(char *s, int c);

#endif