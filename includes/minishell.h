/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:03:37 by jsabound          #+#    #+#             */
/*   Updated: 2023/09/05 17:48:35 by kgezgin          ###   ########.fr       */
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
#define SIMPLE_QUOTE 18
#define DOUBLE_QUOTE 19
#define NO_QUOTE 20

extern int in_here_doc;

typedef struct s_arg
{
	char c;
	struct s_arg *next;
} t_arg;

typedef struct s_env
{
	char *env;
	int printable;
	struct s_env *next;
} t_env;

typedef struct s_parsed
{
	char *token;
	int status;
	int quote_status;
	struct s_parsed *next;
} t_parsed;

typedef struct s_cmd
{
	char *command;
	char **arg;
	char **limiter;
	char **hd_file;
	int nb_here_doc;
	int *hd_fd;
	int fd_in;
	int fd_out;
	int is_ok;
	int command_int;
	int *quote_status;
	struct s_cmd *next;
} t_cmd;

typedef struct s_here_doc
{
	char	*line;
	int		fd;
	char	*limiter;
	char	*path;

} t_here_doc;


typedef struct s_data
{
	int	here_doc_exit;
	int cmd_count;
	int pipe_count;
	int parsed_list_size;
	int fd_pipe[2];
	char *path;
	int index;
	int index_2;
	char **env;
	char **path_begining;
	int previous_fd;
	pid_t *pid;
	int i;
	int j;
	int is;
	int	exit_here_doc;
	int	on_here_doc;
	int free_oldpwd;
	int error_status;
	int	exit_no;
	char *pwd_temp;
	char **str_split;
	t_cmd **c_list_temp;
	t_env *envp;
} t_data;

void ft_end(t_cmd **c_list, t_parsed **p_list, t_data *data, t_env **env_list);
int ft_wait(t_data *data);
void ft_unlink(t_cmd *list);
void ft_free_cmd_list(t_cmd **lst);
void free_cmd_content(t_cmd *lst);
void ft_free_p_list(t_parsed **lst, t_data *data);
void ft_free_map(char **str);
void ft_free_all(t_cmd **c_list, t_parsed **p_list, t_data *data, t_env **env_list);
void ft_free_env(t_env **envp);
void ft_free_arg_list(t_arg **arg);

int execution(t_cmd *list, t_parsed *p_list, t_data *data, t_env **env_list);
void redirections(t_cmd *list, t_data *data);
void get_path_and_exec(t_cmd *list, t_parsed *p_list, t_data *data, t_env *env_list);

int hd_execution(t_parsed *p_list, t_cmd *cmd_list, t_data *data);
void generate_hd_file_name(t_cmd *c_list, int i);
int	here_doc(t_cmd *c_list, t_parsed *p_list, t_data *data, int i);
int open_here_doc(char *path);
void	ft_close(t_cmd *c_list, int i);

void ft_open(t_parsed *p_list, t_cmd *c_list, t_data *data);
void fd_file_in(t_parsed *p_list, t_cmd *c_list, t_data *data);
void fd_here_doc(t_cmd *c_list, t_data *data);
void fd_file_out(t_parsed *p_list, t_cmd *c_list, t_data *data);
void fd_append(t_parsed *p_list, t_cmd *c_list, t_data *data);

t_parsed *get_value_i_j(t_parsed *p_list, int *i, int *j);
void get_value_malloc(t_cmd *c_list, int i, int j);
void get_args(t_cmd *cmd_list, t_parsed *parsed_list);
void get_args_utils(t_cmd *c_list, t_parsed *p_list, int *i, int *j);

t_cmd *create_cmd_list(t_parsed *parsed_list, t_data *data);
t_cmd *get_value(t_cmd *cmd_list, t_parsed *parsed_list);
t_cmd *get_fd(t_cmd *cmd_list, t_parsed *parsed_list, t_data *data);

t_parsed *temp_list(t_data *data, char **av, char *str, t_env *env_list);
int get_status(char *str, int prev_status);
void get_command(t_parsed *list, t_data *data, t_env *env_list);

t_env *my_lstnew_env(char *str, int nb);
t_arg *my_lstnew_arg(char c);
t_cmd *my_lstnew_cmd();
t_parsed *my_lstnew(char *content, int status);
void my_lstadd_back_env(t_env **lst, t_env *new);
void my_lstadd_back_arg(t_arg **lst, t_arg *new);
void my_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void my_lstadd_back(t_parsed **lst, t_parsed *new);
void print_list(t_parsed *token);
void print_env(t_env *token);
void print_arg(t_arg *token);
void print_cmd_list(t_cmd *token);

void init_data(t_data *data, int exit_no, t_env *env);

int is_path(char *str);
char *path_check(t_data *data, t_cmd *list);
void ft_error_path(t_data *data, char *temp, t_cmd *list);
void ft_path(char **envp, t_data *data);

int ft_strcmp(char *s1, char *s2);

void exec_builtin(t_cmd *c_list, t_parsed *p_list, t_env *env_list, t_data *data);
int check_builtin(t_parsed *p_list);
size_t get_lenght(char *str, char c);

t_env *exec_export(t_cmd *c_list, t_env *env_list);
int export_utils_1(char *str);
void export(t_env *env_list);
int export_check(char *str);
// int					export_utils_2(char *env, char *arg, int lenght);
int export_utils_2(char **env, char *arg, int lenght);
void export_utils_3(t_env *temp, int check, t_env *env_list, char *str);

t_env *exec_unset(t_cmd *c_list, t_env **env_list);
void unset_utils(char *str, t_env **env_list);

void exec_echo(t_cmd *c_list);
int check_param_echo(char *str);
void exec_env(t_env *e_list, t_cmd *c_list);
// void exec_exit(t_cmd *c_list, t_parsed *p_list);

void exec_pwd(t_cmd *c_list);
t_env *exec_cd(t_cmd *c_list, t_env *env_list, t_data *data);
int nb_of_arg(char **arg);
int cd_to_oldpwd(t_env *env_list, char *oldpwd);
int cd_to_home(t_env *env_list);
t_env *update_pwd(char *oldpwd, t_env *env_list, char *buf, t_data *data);
char *get_pwd(t_env *env_list);

t_env *get_env(t_env *env_list, char **env);
char **env_char(t_env *env_list);
t_env	*env_i(void);

void execution_loop(t_cmd *list, t_parsed *p_list, t_data *data, t_env *env_list);
void loop_utils_1(t_cmd **c_list, t_parsed **p_list, t_data *data, t_env **env_list);
void loop_utils_1_2(t_data *data, t_cmd *c_temp);
void loop_utils_1_3(t_data *data);
void loop_utils_2(t_cmd **list, t_parsed **p_list, t_data *data, t_env **env_list);

char *get_checked_arg(t_parsed *p_list, t_env *env_list, t_data *data);
char *is_expand(t_parsed *p_list, t_env *env_list, t_data *data);
int get_expand_value(char *str, t_arg **arg_list, t_env *env_list, t_data *data);
int is_permutable(char *arg, char *env);
char *convert_list_to_str(t_arg *list);
int	*get_char_status(t_arg *list, int tablen);
int str_malloc_len(int *tab, int tablen);
int get_tab_len(t_arg *list);
char *get_res(t_arg *list, int *tab, char *res);
int ret_expend(char *str);
int nb_quote(char *str);
void get_fork_status(t_arg **arg_list, t_data *data);
void    signal_ctrl_c_here_doc(int signo);





		//////////////////////////////////////////////////////
		//													//
		//													//
		// 					  PARSING						//
		//													//
		//													//
		//////////////////////////////////////////////////////



char	**mr_split(char *str, char *charset, t_data *data);
int		len_split(char *str, char *charset);
int		check(char *str);
int		check_double_quote(char *str);
int		check_simple_quote(char *str);
int		check_chevron_out(char *str);
int		check_chevron_in(char *str);
void    signal_ctrl_c(int signo);
void	signal_ctrl_slash(int signo);
void	signal_ctrl_backslash(int signo);
void	signal_ctrl_d(void);
int		check_between_pipe(char *str);
int		check_first_char(char *str);
int		check_pipe(char *str);
int		check_metacaractere(char *str);
int		check_metacaractere2(char *str);
void	exec_exit(char *str);
void	exit_char(char *str);
void	exit_classic(char *str);

#endif
