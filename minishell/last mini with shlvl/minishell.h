/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylambark <ylambark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 00:46:42 by ylambark          #+#    #+#             */
/*   Updated: 2022/12/01 01:43:08 by ylambark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>

# define EQUAL 0
# define WORD -1
# define SPACE ' '
# define NEW_LINE '\n'
# define QOUTE '\''
# define DOUBLE_QUOTE '\"'
# define DOLLAR '$'
# define PIPE '|'
# define IN_REDIR '<'
# define OUT_REDIR '>'
# define HERE_DOC 4
# define DOUBLE_OUT 5
# define READING 0
# define EXECUTING 1
# define IN_DQUOTE 0
# define IN_QUOTE 1
# define GENERAL 2
# define CMD	0
# define RED     "\033[31m"
# define RESET   "\033[0m"
# define GREEN	"\033[32m" 

typedef struct s_one_elem		t_one_element;
typedef struct s_one_redir_elem	t_one_red_element;
typedef union u_cmd_pipe		t_cmd_or_pipe;
typedef struct s_one_node_tree	t_one_node_tree;
typedef struct s_node_pipe		t_node_pipe;
typedef struct s_head_redir	t_head_redir;

typedef struct s_fd
{
	int	in;
	int	out;
}	t_fd;

typedef struct s_one_cmd
{
	char			**args;
	char			**env;
	t_fd			fd;
	t_head_redir	*redir;
}	t_one_cmd;

typedef struct s_node_pipe
{
	t_one_node_tree	*left;
	t_one_node_tree	*right;
}	t_node_pipe;

typedef union u_cmd_pipe
{
	t_node_pipe	*pipe;
	t_one_cmd	*cmd;
}	t_cmd_or_pipe;

typedef struct s_one_node_tree
{
	int				type;
	t_cmd_or_pipe	*content;
}	t_one_node_tree;

typedef struct s_tree_root
{
	t_one_node_tree	*root;	
}	t_tree_root;

typedef struct s_one_elem
{
	char			*content;
	int				len;
	int				type;
	int				state;
	t_one_element	*next;
	t_one_element	*prev;
}	t_one_element;

typedef struct s_lexer_lst
{
	t_one_element	*head;
	t_one_element	*tail;
	int				size;
}	t_lexer_lst;

typedef struct s_env_one
{
	char				*key;
	char				*value;
	struct s_env_one	*next;
	struct s_env_one	*prev;
}	t_env_one_element;

typedef struct s_all_env
{
	t_env_one_element	*head;
	char				**env;
	int					size;
}	t_all_env;

typedef struct s_data
{
	int			exit_status;
	int			shlvl;
	int			shell_state;
	int			pid;
	int			which;
	t_all_env	*ev;
	t_lexer_lst	*lex;
	t_tree_root	*tree;
	int			is_env_allocated;
	char		**env;
}	t_data;

typedef struct s_one_redir_elem
{
	char				*arg;
	int					type;
	t_one_red_element	*next;
}	t_one_red_element;

typedef struct s_head_redir
{
	t_one_red_element	*head;
	t_one_red_element	*tail;
	int					size;
}	t_head_redir;

t_data						g_data;

int					ft_strlen(char *s);
int					ft_isalnum(int c);
int					ft_strisspace(char *str);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strndup(char *s1, int n);
char				*ft_strdup(char *s1);
char				*ft_substr(char *s, unsigned int start, size_t len);
int					ft_strchr(char *s, int c);
int					ft_isnum(char *num);
int					ft_isalpha(char c);
int					check_equal_sign(char **arg);
char				**ft_split_for_env(char *arg);
int					ft_isspace(char c);
int					check_special_char(char c);
int					ft_perror(char *msg, char *reason);
int					ft_puterr(char *cmd, char *reason, char *msg, int err_num);
int					ft_strjoin_echo(t_one_cmd **cmd, t_one_element *head, \
				char **env, int i);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				*ft_strjoin_directory(char *s1, char *s2);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strjoin_export(t_one_cmd **cmd, t_one_element *head, \
				char **env, int i);
static int			bigstr(char *s, char c);
int					ft_atoi(char *str);
static char			*test(long *n, long *i, int *k, char *p);
char				*ft_itoa(int n);
static int			smalstr(char *s, char c);
static char			*skip(char *s, char c);
char				**ft_split(char *s, char c);
size_t				ft_strlen_gnl(char *s);
int					ft_strchr_gnl(char *s1, char c);
char				*read_all(int fd, char *text);
char				*get_line(char *text);
char				*new_txt(char *text);
char				*get_next_line(int fd);
void				quotes_redir_counter(t_one_element **one_ele, \
				int type, int *i);
int					check_if_redir(int type);
char				*check_redir_type(int type);
void				cd_dir_change_in_env(t_all_env *env, char *cwd, char *owd);
int					ft_cd(t_one_cmd *cmd, char ***env);
int					ft_echo(t_one_cmd *cmd, t_one_element *head, char **env);
int					if_flag(char *flag);
int					check_echo_args(char **arg);
int					echo_cmd_check(t_one_element *head, char **env);
void				add_number_to(int *i, int to_add);
void				cmd_state_check(t_one_element **head, \
				char **env, int *value);
int					ft_env(t_one_cmd *cmd, char **env);
t_one_element		*check_quote_unclose(t_one_element **elem, int type);
t_one_element		*white_space_skipper(t_one_element *elem, int flag);
int					check_err_syntax(t_lexer_lst *head);
int					check_redir_err(t_one_element *elem);
int					check_pipe_err(t_one_element *elem);
int					counter_args_exit(char **arg);
int					check_exit_arg(char **arg);
int					ft_exit(t_one_cmd *cmd, char **env);
int					ft_export(char ***env, t_one_cmd *cmd, t_one_element *head);
void				state_handler(t_one_element **head, char **env, int *value);
int					check_export_cmd(t_one_element *head, char **env);
void				sort_env_for_export(t_all_env *env);
void				print_env_sorted_export_noparam(t_all_env *env);
void				check_index(t_all_env *env, char *arg, \
				char **tmp, int index);
char				*get_value_of_env(char *key, t_all_env *env);
t_env_one_element	*search_element_struct_env(t_all_env *env, char *key);
char				*search_element_array_env(char *key, char **env);
char				*find_value_expand_env(char **line, char **env);
char				*env_value_expand(char *line, char **env);
void				del_one_element_env(t_all_env *env, \
				t_env_one_element *elem);
void				free_all_srtuct_env(t_all_env *env);
char				**from_struct_to_array(t_all_env *env);
void				env_var_handler(t_all_env *env, t_one_cmd *cmd, \
				t_one_element *head);
t_one_element		*search_key_all_env(t_one_element *head, \
				char *arg, char **env);
void				swap_env_elem(t_env_one_element *from, \
				t_env_one_element *to);
void				delete_env_for_unset(char *arg, t_all_env *env);
void				expand_env_element(t_one_element **ptr, \
							t_all_env *env, char **args, int *i);
t_tree_root			*init_tree(t_tree_root *root);
int					counter_number_of_cmds(t_one_node_tree *head);
void				free_tree(t_one_node_tree *elem);
t_one_node_tree		*init_new_cmd_node(char **arg, char **env, \
				t_head_redir *red);
void				parse_free(t_tree_root *head);
void				parse_lex_free(t_lexer_lst *lex, t_tree_root *head);
void				cmd_free(t_one_cmd *cmd);
void				double_dimension_free(char **arg);
int					check_if_no_element(t_lexer_lst *head);
t_lexer_lst			*lexer_lst_init(t_lexer_lst *head);
t_one_element		*create_new_lexer_element(char *cnt, \
				int len, int type, int state);
void				add_lexer_element_back(t_lexer_lst *head, \
				t_one_element *new);
void				free_lexer_all_struct(t_lexer_lst *head);
t_all_env			*init_env(t_all_env *env);
t_env_one_element	*create_new_elem_env(char *line);
void				add_env_elem(t_all_env *env, t_env_one_element *new);
t_all_env			*create_all_env_struct(char **tab);
void				add_back_element_redir(t_head_redir *head, \
				t_one_red_element *new);
t_one_red_element	*creat_element_redir(char *arg, int type);
t_head_redir		*redir_head_lst_init(t_head_redir *head);
void				free_redir_list(t_head_redir *head);
int					is_buitlin(char *command);
void				identify_builtin(t_one_cmd *command, char ***env, \
				t_one_element *head);
void				swap_fd_var(int *old_fd, int new_fd);
void				fd_handler_builtin(t_one_cmd *my_cmd);
void				fd_handler_execve(t_one_cmd *my_cmd, int fd[2]);
void				check_last_pid(int pid, int counter, int cmds_number);
void				builtin_ex(t_one_cmd *my_cmd, char ***env, \
				t_one_element *head);
int					cmd_executor(t_one_cmd *my_cmd, char **env, int fd[2]);
int					builtin_exec(t_one_node_tree *node, char ***env, \
				t_one_element *head, int fd[2]);
void				main_execute(t_one_node_tree *node, char ***env, \
				int cmds_number, \
					t_one_element *lexer_head);
int					*search_r_l(t_one_node_tree *ptr);
char				*get_path_cmd(char *cmd, char **env);
char				*check_dot_slach(char *cmd_to_check, char **env);
char				*get_cmd(char *command, char **env);
void				handle_sigaction(int sig, siginfo_t *tmp, void *p);
void				init_sigaction(t_data *data);
int					identify_redirections(t_lexer_lst *tk, char *rd_line, \
				int i, int *state);
int					identifie_line(t_lexer_lst *tk, char *rd_line, \
				int i, int *state);
int					word_lexer_type_get(t_lexer_lst *tk, char *str, int state);
int					env_key_lexer_type_get(t_lexer_lst *tk, \
				char *str, int state);
void				check_modify_state_of_quote(t_lexer_lst *tk, char *str, \
			int *state, int flag);
t_lexer_lst			*lexer(char *rd_line);
t_head_redir		*heredoc_parse_handler(t_head_redir *red, \
			char *arg, char **env);
t_one_node_tree		*pipe_parse_handler(t_one_element **ptr);
char				*quotes_parse_handler(char *str, t_one_element **ptr, \
			int type, t_all_env *env);
void				word_parse_handler(t_one_element **ptr, char **arg, int *i);
t_head_redir		*redir_parse_handler(t_one_element **ptr, \
				t_head_redir *red, t_all_env *env);
int					cmd_parser2(t_one_element **ptr, t_all_env *env, \
				t_head_redir *red, char **arg);
t_one_node_tree		*cmd_parser(t_one_element **ptr, t_all_env *env);
int					my_parser(t_tree_root **head, t_one_element *ptr, \
				t_all_env *env);
int					arg_counter(t_one_element *one_elem);
int					ft_pwd(void);
void				redir_ex(t_head_redir *head, t_fd *fd);
void				redirin_ex(t_one_red_element *redir, int *fd_in);
int					ft_unset(t_one_cmd *cmd, char ***env_2d);
void				ft_wait(void);
void				mini_shell_executor(char **env);
void				assign_SHLVL(char ***env);
void				assign_global_data(char **env);
void				run_new_minishell(char ***env);
int					readline_luncher(char **rd_line, char ***env);
int					main(int c, char **v, char **env);
void				init_global_var(t_data *data);

#endif