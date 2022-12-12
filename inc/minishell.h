/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:53:35 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/16 15:05:42 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <pwd.h>
# include <errno.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <dirent.h>
# include <fcntl.h>
# include "../libft/inc/libft.h"

# define READ 0
# define WRITE 1
# define NEW_LINE '\n'
# define ERROR 0
# define OK 1
# define TRUE 0
# define FALSE 1

typedef struct s_var
{
	char			*key;
	char			*value;
}	t_var;

typedef struct s_token
{
	void			*value;
	char			*type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*file;
}	t_redir;

typedef struct s_cmd
{
	char			*name;
	t_list			*args_list;
	t_list			*redir_list;
	int				fd[2];
	int				i;
}	t_cmd;

typedef int			t_pipes[2];

typedef struct s_exec
{
	t_cmd			*cmd;
	t_pipes			*pipes;
	int				nbr_cmds;
	int				count;
}	t_exec;

typedef struct s_glob
{
	int				fork;
	int				signal;
	char			*inpt;
	t_list			*env;
	t_list			*exitstatus;
	t_list			*cl;
	int				error;
	int				len;
	t_token			*start;
	int				hd_sign;
}	t_glob;

struct s_glob		g_g;

/*
**	error.c
*/
int					ft_error(char *msg, char *add, int on, int err);
int					ft_errormod(char *msg, char *add, int on, int err);
void				ft_upexitstat(int error);

/*
**	exit.c
*/
void				exit_msg_handler(void);
void				free_and_restart(void);
int					free_all_and_exit(void);

/*
**	signals.c
*/
void				init_signal(void);
void				handle_signal(int signum);

/*
**	utils.c
*/
void				free_if(void *elem);
void				free_array(char **array);
int					tablen(char **array);

/*
**  BUILTINS/
*/
int					env_cmd(t_list *env);
int					pwd_cmd(void);
int					cd_cmd(int len, char **args, t_list **env);
int					echo_cmd(int len, char **args);
int					export_cmd(int len, char **args, t_list **env);
int					unset_cmd(int len, char **args, t_list **env);
int					exit_cmd(int agrc, char **arg);

/*
**	cd_utils.c
*/
char				*new_value(char *var, char *old, char *new);
int					change_variable(t_list **env, char *key, char **oldpwd, \
																	char *pwd);
/*
**	export_one_arg.c
*/
int					print_sorted_env(t_list *env);

/*
**  ENVIRONMENT/parse_env.c
*/
int					parse_env(char **envp, t_list **env);

/*
**	edit_var.c
*/
int					edit_var(t_list **env, char *key, char *value);
int					append_var(t_list **env, char *key, char *app);
t_var				*create_var(char *str);

/*
**	init_var.c
*/
void				init_var(void);

/*
**	utils_var.c
*/
void				free_var(void *var);
char				*search_var(t_list *env, char *key);
char				**list_to_tab(t_list *env);

/*
**	EXEC/exec.c
*/
int					exec_handler(t_list *cmd_list, t_list **env);

/*
**	child_process.c
*/
int					child_process(t_exec exec, t_list **env);

/*
**	exec_builtin.c
*/
int					exec_builtin(char *name, t_list *args, t_cmd *cmd, \
																t_list **env);
int					check_builtin(char *cmd);
char				**args_list_to_tab(t_list *args_list);

/*
**	exec_commands.c
*/
int					exec_forked_commands(t_list *cmds, t_list **env);

/*
**	exec_commands_utils.c
*/
int					get_absolute_path(char **abs_path, char **cmd, t_list *env);

/*
**	handle_fds.c
*/
void				handle_fds(t_pipes *pipes, int count, int nbr_cmds, \
																	t_cmd *cmd);

/*
**	handle_files.c
*/
int					create_file(int type, char *filename);

/*
**	handle_pipes.c
*/
t_pipes				*open_pipes(int nbr_cmds);
void				close_pipes(t_pipes *pipes, int nbr_cmds);

/*
**	handle_redirections.c
*/
int					handle_redirections(t_cmd *cmd, int fd[2]);
void				reinit_redirections(int fd[2]);

/*
**	handle_files_utils.c
*/
int					check_permissions(char *filename);

/*
** -------------------------- /TOKEN/ --------------------------------
*/

/*
** cmd_list.c
*/
void				ft_tok_to_cmd(void);

/*
** cmd_clear.c
*/
void				ft_cl_clear(void);

/*
** cmd_utils.c
*/

void				ft_gib_order(void);
int					ft_redir_type(t_token *start);

/*
** token.c 
*/
void				ft_token(char *buf);

/*
** token2.c
*/
void				ft_pretoken(char *input);
void				ft_retoken(void);

/*
** token_merge.c
*/
void				ft_merge_double(void);
void				ft_merge_tok(t_token *tok, int val, int type);
void				ft_merge_alpha_var(void);

/*
** token_remove.c
*/
void				ft_memdel(void **truc);
void				ft_free_tok(t_token	*tok);
void				ft_free_toklist(void);

/*
** token_test.c
*/
void				ft_print_token(void);
void				ft_revprint_token(void);
void				ft_print_cl(void);

/*
** tokenutils.c
*/
t_token				*ft_create_token(void *content);
t_token				*ft_get_lasttok(void);
void				ft_remove_token(t_token *del);
void				ft_remove_space(void);
char				*ft_token_type(char c);

/*
** tokenutils2.c
*/
void				ft_change_type(t_token *tok, char *type);
void				ft_change_value(t_token *tok, char *value);
int					ft_istype(t_token *tok, char *type);
int					ft_isredir(t_token *tok, int pipe);
int					ft_islit(t_token *tok);

/*
**  ----------------------- /PARSING/ -----------------------------
*/

/*
** parsing.c
*/
void				ft_parsing(void);

/*
** parserror.c
*/
void				ft_synerror(void);

/*
** quotes.c
*/
void				ft_check_quotes(void);
void				ft_quotes(void);

/*
** quotes2.c
*/
void				ft_removequotes(void);

/*
** variable.c
*/
void				ft_prep_variable(void);
void				ft_expend_variable(void);

/*
** variable2.c
*/
char				**ft_splitmod(t_token *start);
int					ft_expend_variable3(t_token **start, char **tab);

/*
** ------------------------ /HEREDOC/ -------------------------------
*/

/*
** heredoc_parsing.c
*/

void				ft_heredoc(void);

/*
** heredoc_token.c
*/

char				*ft_expendline(char *line);

/*
** heredoc_utils.c
*/

char				*ft_token_typemod(char c);
t_token				*ft_getlasttokmod(t_token *start);
void				ft_print_tokenmod(t_token *start);
int					ft_double_redir_left(char **name);

/*
** heredoc_utils2.c
*/

char				*ft_delim_quote(t_token *start);
char				*ft_get_delim(t_token *tok, int *flag);

/*
** heredoc_signals.c
*/
void				ft_init_heredoc_signals(void);

/*
** heredoc_var2.c
*/
int					ft_isspace(int c);
void				complete_line_alphanum(char *line, char buf[1024], \
																int *i, int *l);
void				complete_line_spaces(char *line, char buf[1024], \
																int *i, int *l);
void				reset_buf(char buf[1024], int *i);
void				get_var_value(char buf[1024], char *var_value, int *i);

#endif
