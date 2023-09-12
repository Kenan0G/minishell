/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:03:37 by jsabound          #+#    #+#             */
/*   Updated: 2023/09/12 19:27:15 by jsabound         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define REDIR_IN 1
# define FILE_IN 2
# define FILE_OUT 3
# define REDIR_OUT 4
# define PIPE 5
# define COMMAND 6
# define ARG 7
# define HERE_DOC 8
# define APPEND 9
# define LIMITER 10
# define ECHO 11
# define CD 12
# define PWD 13
# define EXPORT 14
# define UNSET 15
# define ENV 16
# define EXIT 17
# define SIMPLE_QUOTE 18
# define DOUBLE_QUOTE 19
# define NO_QUOTE 20

extern int			g_in_here_doc;

typedef struct s_arg
{
	char			c;
	struct s_arg	*next;
}					t_arg;

typedef struct s_env
{
	char			*env;
	int				printable;
	struct s_env	*next;
}					t_env;

typedef struct s_parsed
{
	char			*token;
	int				status;
	int				quote_status;
	struct s_parsed	*next;
}					t_parsed;

typedef struct s_cmd
{
	char			*command;
	char			**arg;
	char			**limiter;
	char			**hd_file;
	int				nb_here_doc;
	int				err_no;
	int				*hd_fd;
	int				fd_in;
	int				fd_out;
	int				is_ok;
	int				command_int;
	int				*quote_status;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_here_doc
{
	char			*line;
	int				fd;
	char			*limiter;
	char			*path;

}					t_here_doc;

typedef struct s_data
{
	int				here_doc_exit;
	int				nb_quote;
	int				len;
	int				set;
	int				is_quote;
	int				cmd_count;
	int				pipe_count;
	int				parsed_list_size;
	int				fd_pipe[2];
	int				index;
	int				index_2;
	int				previous_fd;
	int				i;
	int				j;
	int				is;
	int				on_here_doc;
	int				free_oldpwd;
	int				error_status;
	int				exit_no;
	char			**env;
	char			**path_begining;
	char			*path;
	char			*pwd_temp;
	char			**str_split;
	pid_t			*pid;
	t_env			*envp;
	t_cmd			**c_list_adress;
	t_parsed		**p_list_adress;
	t_cmd			*c;
	t_parsed		*p;
	t_env			*e;
}					t_data;

////////// BUILTINS //////////

// --- cd.c ---

t_env				*exec_cd(t_cmd *c_list, t_env *env_list, t_data *data);
void				cd_utils(t_cmd *c_list, t_data *data, char *oldpwd);
int					nb_of_arg(char **arg);
int					cd_to_home(t_env *env_list);

// --- cd_utils.c ---

t_env				*update_pwd(char *oldpwd, t_env *env_list, char *buf,
						t_data *data);
void				update_cd_utils(t_env *temp, char *pwd, char *oldpwd,
						char *path);
char				*get_pwd(t_env *env_list);

// --- echo.c ---

void				exec_echo(t_cmd *c_list);
void				display(t_cmd *c_list, int i);
int					check_param_echo(char *str);

// --- env.c ---

void				exec_env(t_env *e_list, t_cmd *c_list);

// --- export.c ---

t_env				*exec_export(t_cmd *c_list, t_env *env_list);
void				exec_export_utils(t_cmd *c_list, t_env *env_list,
						t_env *temp, int check);
int					export_utils_1(char *str);
int					export_utils_2(char *arg, int lenght, t_env *temp);
void				export_utils_3(t_env *temp, int check, t_env *env_list,
						char *str);

//  --- export_utils.c ---

void				export(t_env *env_list);
void				display_export(char **env, int i, int j);
char				**sort_env(t_env *env_list);
int					export_check(char *str);

// --- pwd.c ---

void				exec_pwd(t_cmd *c_list);

// --- unset.c ---

t_env				*exec_unset(t_cmd *c_list, t_env **env_list);
void				unset_utils(char *str, t_env **env_list);
size_t				get_lenght(char *str, char c);

////////// CLEANING //////////

// --- end_program.c ---

void				ft_end(t_cmd **c_list, t_parsed **p_list);
void				ft_free_all(t_cmd **c_list, t_parsed **p_list);
int					ft_wait(t_data *data);
void				ft_unlink(t_cmd *list);
void				ft_free_map(char **str);

// --- free_data ---

void				ft_free_cmd_list(t_cmd **lst);
void				free_cmd_content(t_cmd *lst);
void				ft_free_p_list(t_parsed **lst);
void				ft_free_env(t_env **envp);
void				ft_free_arg_list(t_arg **arg);

////////// EXPANDS //////////

// --- look_for_expand.c ---

char				*look_for_expand(t_parsed *p_list, t_env *env_list,
						t_data *data);
int					copy_in_list(int i, char *str, t_arg **list, t_data *data);
int					update_index(char *str, int i, int ret_expand);
int					skip_single_quote(int i, t_arg **list, char *str,
						t_data *data);

// --- permute_expand.c ---

int					permute_expand(char *str, t_arg **arg_list, t_env *env_list,
						t_data *data);
int					special_cases(t_arg **arg_list, char *str, t_data *data);
int					is_permutable(char *arg, char *env);
int					permute(int i, int len, char *str, t_arg **arg_list);
int					var_len(char *str);

// --- convert_list_to_str.c ---

int					*get_status_tab(t_arg *list, int tablen);
void				tab_quote(int i, int *tab, t_arg *temp, int tablen);
int					get_tab_len(t_arg *list);
int					str_malloc_len(int *tab, int tablen);
char				simple_or_double(char c);

// --- environment.c ---

t_env				*get_env(t_env *env_list, char **env);
void				set_value(t_env **temp, char **env, int i);
char				**env_char(t_env *env_list);
t_env				*env_i(void);

// --- expand.c ---

char				*is_expand(t_parsed *p_list, t_env *env_list, t_data *data);
char				*convert_list_to_str(t_arg *list);
void				get_fork_status(t_arg **arg_list, t_data *data);
int					nb_quote(char *str);
char				*get_res(t_arg *list, int *tab, char *res);

////////// HERE_DOC //////////

// --- here_doc.c ---

int					hd_execution(t_parsed *p_list, t_cmd *cmd_list,
						t_data *data);
int					here_doc(t_cmd *c_list, t_parsed *p_list, t_data *data,
						int i);
int					readline_in_here_doc(t_data *data, t_here_doc *var);
int					return_here_doc(t_data *data, t_here_doc *var);

// --- here_doc_utils.c ---

void				generate_hd_file_name(t_cmd *c_list, int i);
void				*starthd(void);
void				ft_close(t_cmd *c_list, int i);
int					open_here_doc(char *path);

////////// EXEC //////////

////////// EXECUTION_LIST //////////

// --- list_exec.c ---

t_cmd				*create_cmd_list(t_parsed *parsed_list, t_data *data);
t_cmd				*get_value(t_cmd *cmd_list, t_parsed *parsed_list);
t_cmd				*get_fd(t_cmd *cmd_list, t_parsed *parsed_list,
						t_data *data);
void				run_here_doc(t_cmd *c_list, t_parsed *p_list, t_data *data);

// --- list_exec_fd.c ---

void				ft_open(t_parsed *p_list, t_cmd *c_list, t_data *data);
void				fd_file_in(t_parsed *p_list, t_cmd *c_list, t_data *data);
void				fd_here_doc(t_cmd *c_list, t_data *data);
void				fd_append(t_parsed *p_list, t_cmd *c_list, t_data *data);
void				fd_file_out(t_parsed *p_list, t_cmd *c_list, t_data *data);

// --- list_exec_value.c ---

t_parsed			*get_value_i_j(t_parsed *p_list, int *i, int *j);
void				get_value_malloc(t_cmd *c_list, int i, int j);
void				get_args(t_cmd *cmd_list, t_parsed *parsed_list);
void				get_args_utils(t_cmd *c_list, t_parsed *p_list, int *i,
						int *j);
int					check_arg(t_cmd *c_list, t_parsed *p_list, int i);

////////// EXECUTION_RUN //////////

// --- execution.c ---

int					execution(t_cmd *list, t_parsed *p_list, t_data *data,
						t_env **env_list);
void				exec_builtin(t_cmd *c_list, t_parsed *p_list,
						t_env *env_list, t_data *data);
void				get_path_and_exec(t_cmd *list, t_parsed *p_list,
						t_data *data, t_env *env_list);
void				clear_fork(t_cmd *list, t_parsed *p_list, t_data *data,
						t_env *env_list);
void				error(t_data *data, t_parsed *p_list, t_env *env_list);

// --- execution_loop.c ---

void				redirections(t_cmd *list, t_data *data);
void				execution_loop(t_cmd *list, t_parsed *p_list, t_data *data,
						t_env *env_list);
void				setup_exec(t_cmd **c_list, t_parsed **p_list, t_data *data,
						t_env **env_list);
void				go_to_builtin(t_cmd *c_temp, t_parsed *p_temp, t_data *data,
						t_env **env_list);
void				skip_fork(t_cmd **c_list, t_parsed **p_list, t_data *data,
						t_env **env_list);

// --- get_path.c ---

int					is_path(char *str);
char				*path_check(t_data *data, t_cmd *list);
void				ft_error_path(char *temp, t_cmd *list);
void				ft_path(char **envp, t_data *data);

// --- loop_utils.c ---

void				close_if(t_data *data);
void				setup_fd(t_data *data, t_cmd *c_temp);

////////// PARSED_LIST //////////

// --- list_temp.c ---

t_parsed			*temp_list(t_data *data, char *str, t_env *env_list);
int					get_status(char *str, int prev_status);
int					check_builtin(t_parsed *p_list);
void				get_command(t_parsed *list, t_data *data, t_env *env_list);
void				run_expand(t_parsed **temp, t_env *env_list, t_data *data);

char				*get_word_utils(char *temp, int i);

char				*get_word(char *temp, char *str, t_data *data,
						char *charset);
int					create_word2(t_data *data, char *str, char *temp, int i);
int					create_word3(t_data *data, char *str, char *temp, int i);
char				*create_charset2(t_data *data, char *str, int i,
						char *temp);
int					len_split2(int is_quote, char c);
int					len_split3(t_data *data, char *str, int i, char *charset);
int					ft_ischarset(char c, char *charset);

void				run_loop(t_cmd *c_list, t_parsed *p_list, t_env *env_list,
						t_data *data);
t_env				*my_lstnew_env(char *str, int nb);
t_arg				*my_lstnew_arg(char c);
t_cmd				*my_lstnew_cmd(void);
t_parsed			*my_lstnew(char *content, int status);
void				my_lstadd_back_env(t_env **lst, t_env *new);
void				my_lstadd_back_arg(t_arg **lst, t_arg *new);
void				my_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void				my_lstadd_back(t_parsed **lst, t_parsed *new);
void				print_list(t_parsed *token);
void				print_env(t_env *token);
void				print_arg(t_arg *token);
void				print_cmd_list(t_cmd *token);

void				init_data(t_data **data, int exit_no, t_env *env);

int					ft_strcmp(char *s1, char *s2);

//////////////////////////////////////////////////////
//													//
//													//
// 						PARSING						//
//													//
//													//
//////////////////////////////////////////////////////

char				**mr_split(char *str, char *charset, t_data *data);
int					len_split(char *str, char *charset, t_data *data);
int					check(char *str);
int					check_double_quote(char *str);
int					check_simple_quote(char *str);
int					check_chevron_out(char *str);
int					check_chevron_in(char *str);
void				signal_ctrl_c(int signo);
void				signal_ctrl_slash(int signo);
void				signal_ctrl_backslash(int signo);
void				signal_ctrl_c_here_doc(int signo);
void				signal_ctrl_c_in_child(int signo);
void				signal_ctrl_d(void);
int					check_between_pipe(char *str);
int					check_first_char(char *str);
int					check_pipe(char *str);
int					check_metacaractere(char *str);
int					check_metacaractere2(char *str);
void				exit_char(t_cmd *lst, t_parsed *p_list, t_data *data,
						t_env *env_list);
void				exit_classic(t_cmd *lst, t_parsed *p_list, t_data *data,
						t_env *env_list);
void				exec_exit(t_cmd *lst, t_parsed *p_list, t_data *data,
						t_env *env_list);
int					check_metacaractere3(int i, char *str);
int					check_pipe2(char *str);
int					check_pipe3(char *str);
#endif
