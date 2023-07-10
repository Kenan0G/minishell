/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:03:37 by jsabound          #+#    #+#             */
/*   Updated: 2023/07/10 20:41:58 by kgezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define REDIR_IN 1
#define FILE_IN 2
#define FILE_OUT 3
#define REDIR_OUT 4
#define PIPE 5
#define COMMAND 6
#define ARG 7
#define HERE_DOC 8
#define APPEND 9
#define LIMITER 10
#define ECHO 11
#define CD 12
#define PWD 13
#define EXPORT 14
#define UNSET 15
#define ENV 16
#define EXIT 17

typedef struct s_cmd
{
	char			*command;
	char			**arg;
	char			**limiter;
	char			**hd_file;
	int				nb_here_doc;
	int				*hd_fd;
	int				fd_in;
	int				fd_out;
	int				is_ok;
	int				command_int;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_parsed
{
	char			*token;
	int				status;
	struct s_parsed	*next;
} t_parsed;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	int				cmd_count;
	int				parsed_list_size;
	int				fd_pipe[2];
	char			*path;
	int				index;
	char			**env;
	char			**path_begining;
	int				previous_fd;
	pid_t			*pid;
	int				i;
	int				j;
	char			**str_split;
	t_env			*envp;
} t_data;

void				ft_end(t_cmd **c_list, t_parsed **p_list, t_data *data, t_env *env_list);
void				ft_wait(t_data *data);
void				ft_unlink(t_cmd *list);
void				ft_free_cmd_list(t_cmd **lst);
void				free_cmd_content(t_cmd *lst);
void				ft_free_p_list(t_parsed **lst, t_data *data);
void				ft_free_map(char **str);
void				ft_free_all(t_cmd **c_list, t_parsed **p_list, t_data *data);
void				ft_free_env(t_env **envp);


int					execution(t_cmd *list, t_parsed *p_list, t_data *data, t_env *env_list);
void				execution_loop(t_cmd *list, t_parsed *p_list, t_data *data, t_env *env_list);
void				redirections(t_cmd *list, t_data *data);
void				get_path_and_exec(t_cmd *list, t_parsed *p_list, t_data *data, t_env *env_list);

void				hd_execution(t_parsed *p_list, t_cmd *cmd_list);
void				generate_hd_file_name(t_cmd *c_list, int i);
int					here_doc(char *limiter, char *path);
int					open_here_doc(char *path);

void				ft_open(t_parsed *p_list, t_cmd *c_list, t_data *data);
void				fd_file_in(t_parsed *p_list, t_cmd *c_list, t_data *data);
void				fd_here_doc(t_cmd *c_list, t_data *data);
void				fd_file_out(t_parsed *p_list, t_cmd *c_list, t_data *data);
void				fd_append(t_parsed *p_list, t_cmd *c_list, t_data *data);

t_parsed			*get_value_i_j(t_parsed *p_list, int *i, int *j);
void				get_value_malloc(t_cmd *c_list, int i, int j);
void				get_args(t_cmd *cmd_list, t_parsed *parsed_list);
void				get_args_utils(t_cmd *c_list, t_parsed *p_list, int *i, int *j);

t_cmd				*create_cmd_list(t_parsed *parsed_list, t_data *data);
t_cmd				*get_value(t_cmd *cmd_list, t_parsed *parsed_list);
t_cmd				*get_fd(t_cmd *cmd_list, t_parsed *parsed_list, t_data *data);

t_parsed 			*temp_list(t_data *data, char **av, char *str);
int					first_char(char *str, int prev_status);
void				get_command(t_parsed *list, t_data *data);

t_env				*my_lstnew_env(char *str);
void				my_lstadd_back_env(t_env **lst, t_env *new);
void				my_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd				*my_lstnew_cmd();
void				my_lstadd_back(t_parsed **lst, t_parsed *new);
t_parsed			*my_lstnew(char *content, int status);
void				print_list(t_parsed *token);
void				print_env(t_env *token);
void				print_cmd_list(t_cmd *token);

void				init_data(t_data *data, char **env);

int					is_path(char *str);
char				*path_check(t_data *data, t_cmd *list);
void				ft_error_path(t_data *data, char *temp, t_cmd *list);
void				ft_path(char **envp, t_data *data);

int					ft_strcmp(char *s1, char *s2);

void				exec_builtin(t_cmd *c_list, t_parsed *p_list, t_data *data, t_env *env_list);
void				exec_echo(t_cmd *c_list, t_parsed *p_list, t_data *data);
int					check_builtin(t_parsed *p_list);

t_env				*get_env(t_env *env_list, char **env);
char				**env_execve(t_env *env_list);


// 
// 
// PARSING  
// 
// 
// 

char **mr_split(char *str, char *charset);


#endif