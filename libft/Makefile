# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 12:55:59 by jsabound          #+#    #+#              #
#    Updated: 2023/02/26 12:23:48 by jsabound         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./srcs/
SRCS = ft_strlen.c\
	   ft_isalpha.c\
	   ft_isalnum.c\
	   ft_isascii.c\
	   ft_isdigit.c\
	   ft_isprint.c\
	   ft_memset.c\
	   ft_bzero.c\
	   ft_memcpy.c\
	   ft_memmove.c\
	   ft_strlcpy.c\
	   ft_strlcat.c\
	   ft_toupper.c\
	   ft_tolower.c\
	   ft_strchr.c\
	   ft_strrchr.c\
	   ft_strncmp.c\
	   ft_memchr.c\
	   ft_memcmp.c\
	   ft_strnstr.c\
	   ft_atoi.c\
	   ft_calloc.c\
	   ft_strdup.c\
	   ft_substr.c\
	   ft_strjoin.c\
	   ft_strtrim.c\
	   ft_split.c\
	   ft_itoa.c\
	   ft_strmapi.c\
	   ft_striteri.c\
	   ft_putchar_fd.c\
	   ft_putstr_fd.c\
	   ft_putendl_fd.c\
	   ft_printf.c\
	   ft_printf_utils.c\
	   ft_arg.c\
	   ft_putnbr_fd.c\
		ft_lstnew.c\
		 ft_lstadd_front.c\
		 ft_lstsize.c\
		 ft_lstlast.c\
		 ft_lstadd_back.c\
		 ft_lstdelone.c\
		 ft_lstclear.c\
		 ft_lstiter.c\
		 ft_lstmap.c
OBJS = ${SRCS:.c=.o}
NAME = libft.a
CC = gcc
RM = rm -f
.c.o:	
	${CC} -Wall -Wextra -Werror -c $< -o ${<:.c=.o}
${NAME}: ${OBJS}	
	ar rc ${NAME} ${OBJS}
all : ${NAME}

clean :
	${RM} ${OBJS}
fclean : clean	
	${RM} ${NAME} 
re : fclean all
so:
	$(CC) -fPIC $(CFLAGS) $(SRCS)
	gcc -shared -o libft.so $(OBJS)

.PHONY : all clean fclean re
