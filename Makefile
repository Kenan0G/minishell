# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 16:43:53 by vahemere          #+#    #+#              #
#    Updated: 2022/07/23 19:25:18 by vahemere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_DIR = objs
SRCS_DIR = $(shell find srcs -type d)

vpath %.c $(foreach dir, $(SRCS_DIR), $(dir))
SRCS =	minishell.c\
		cd.c\
		cd_utils.c\
		echo.c\
		env.c\
		export.c\
		export_utils.c\
		pwd.c\
		unset.c\
		end_program.c\
		free_data.c\
		convert_list_to_str.c\
		environment.c\
		expand.c\
		look_for_expand.c\
		permute_expand.c\
		here_doc.c\
		here_doc_utils.c\
		execution.c\
		execution_loop.c\
		get_path.c\
		loop_utils.c\
		list_exec_fd.c\
		list_exec_value.c\
		list_exec.c\
		list_temp.c\
		my_lstadd_back.c\
		my_lstnew.c\
		utils.c \
		split.c\
		split2.c\
		split3.c\
		signal.c\
		check.c\
		check_chevron.c\
		check_pipe.c\
		check_quote.c\
		print.c\
		exit.c



OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

DEPS = $(OBJS:%.o=%.d)

NAME = minishell
NORM = norminette

########################### COMPILATION AND FLAGS ###########################

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address

##################################### COLOR ##################################

COLOUR_PURPLE = \033[0;35m
COLOUR_END = \033[0m

##################################### MAIN ###################################

all: $(NAME)

##################################### MANDATORY ##############################

$(NAME): $(OBJS)
	cd libft && make
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) includes/minishell.h libft/libft.a  -lreadline 
	@echo "\n\t$(COLOUR_PURPLE)***EXECUTABLE CREATED SUCCESSFULL***\n\n$(COLOUR_END)"

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -lreadline -o $@ -c $<

$(OBJS_DIR):
	mkdir -p $@
	@echo "\n\t$(COLOUR_PURPLE)OBJECT DIRECTORY CREATED\n\n$(COLOUR_END)"

clean:
	rm -rf $(OBJS) $(OBJS_DIR) $(DEPS) && cd libft && make clean
	@echo "\n\t$(COLOUR_PURPLE)OBJECT DIRECTORY CREATED\n\n$(COLOUR_END)"

fclean: clean
	rm -rf $(NAME) && cd libft && make fclean
	@echo "\n\t$(COLOUR_PURPLE)DELETE EXECUTABLE SUCCESSFULL\n\n$(COLOUR_END)"

norm:
	@echo "$(COLOUR_PURPLE)***CHECK NORM FILES***$(COLOUR_END)"
	@$(NORM)

re: fclean
	make all

.PHONY: all clean fclean norm re

-include $(DEPS)