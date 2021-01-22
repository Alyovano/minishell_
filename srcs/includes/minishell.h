/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:32:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/18 14:41:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_CWD_MAX 2048
# define OK 0
# define FAIL 1
# define READ 0
# define WRITE 1
# define NO_ARGS 0
# define ARGS 1

/*
** Des librairies
*/

# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libftprintfgnl.h"
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <string.h>

int					g_reg;
int					g_errno;

/*
**               Des structures
*/

/*
** (s_user)
** Dans cette struct je vais tenter de garder slm ce qui sera
** utile dans la premiere partie du projet -> Ce qui est relatif au parsing
** aux entrees de l'utilisateur et les infos du systeme
*/

typedef struct		s_user
{
	char			**user_cmd_tab;
	char			*user_input;
	int				split_nb;
	int				chevron_nb;
	t_list			*line;
}					t_user;

/*
** (s_quote)
** Rien de ouf juste quelques token pour verifier les validites
*/

typedef struct		s_quote
{
	int				dquote;
	int				squote;
	int				verif;
	int				len;
	int				dollar_quote;
}					t_quote;

/*
** (s_env)
** **tab = Notre tableau environnmenetal
** **export = Notre tableau range facon export
*/

typedef	struct		s_env
{
	char			**tab;
	char			**export;
	int				swap_token;
}					t_env;

/*
** (s_fd)
** contient les fd utilises dans l'execution
*/

typedef struct		s_fd
{
	int				tmpin;
	int				tmpout;
	int				fdin;
	int				fdout;
}					t_fd;

/*
** (s_dollar)
** Pcq cet algo requier trop de variable a deplacer pour la norme 42
** cette strcut n'est utilisee que dans des cas specifiques,
** elle est donc free independemment des frees de sorties standarts
*/

typedef struct		s_dollar
{
	char			*var_name;
	char			*var_content;
	char			*before_str;
	char			*after_str;
	char			*first_join;
	char			*second_join;
	int				start_cut;
	int				len;
	int				index;
}					t_dollar;

/*
** 		Structures secondaires (Norme | Proprete du code)
*/

typedef struct		s_token_env
{
	int				i;
	int				j;
	int				k;
}					t_token_env;

typedef struct		s_requote_str
{
	char			*new;
	int				i;
	int				j;
	int				token;
}					t_requote_str;

typedef struct		s_export_new_var
{
	char			**new_tab;
	char			*tmp;
	int				i;
	int				j;
	int				position;
}					t_export_new_var;

/*
** (s_int_pack)
*/

typedef struct		s_int_pack
{
	int				i;
	int				j;
	int				k;
}					t_int_pack;

/*
**                 Des fonctions
*/

void				free_all(t_user *start);
int					parsing_input(char *input, t_user *start, t_env *env);
int					check_input_start(t_user *start);
void				error_output_token(int error, char *str, char c);
int					find_char(char *str, char c);
char				**add_str_to_tab(char **tab, char *str);
int					check_backslash(t_list *start);
int					parsing_input_verif1(char *input, t_user *start);
int					parsing_input_verif2(t_user *start);
int					input_to_tab(t_user *start, t_quote *quote);

/*
**          Split
*/

char				*ft_str_n_dup(const char *s1, int size);
void				clean_spaces(t_user *start, t_quote *quote);
void				clean_line(t_user *start, t_quote *quote);
int					first_split_dirty_line(t_user *start, t_quote *quote);
int					init_double_tab_cmd(t_user *start);
int					input_to_tab_verif(t_user *start, t_quote *quote, int i);
void				is_split_tokenize(t_user *start, int i);
void				split_tokenize(t_user *start, t_quote *quote);
char				**tokenize_realloc(char **tab);
void				init_quotes(t_quote *quote, int squote, int dquote);

/*
**          Pipe '|'
*/

int					check_pipe(char *str, t_quote *quote);
void				split_pipe(t_user *start, t_quote *quote);
t_list				*cut_input_to_tab_pipe(t_quote *quote, char *str);

/*
**          Semicolon; Chevron<>  Backslash\\
*/

int					get_backslash(char *str, int i);
int					is_this_splitable(t_user *start, t_quote *quote, int i);
int					is_this_redirectable(t_user *start, t_quote *quote, int i);
int					is_this_redirectable_reverse(t_user *start,
					t_quote *quote, int i);

/*
**                 Quotes
*/

int					quote_get_len_and_validity(t_user *start,
					t_quote *quote, int i);
int					quote_len(char *str);
char				*delete_quote(char *str);
void				init_requote_str(t_requote_str *trs, char *str);
char				*requote_str(char *str);
void				requote_arg(t_list *lst);
void				init_quotes_to_fix(t_quote *quote);
void				init_quotes_to_fix(t_quote *quote);

/*
**          Redirrections
*/

int					get_redirrect(t_list *lst, t_quote *quote);
void				init_redirrect(t_list *lst);
int					check_redirrect(char *str, int i);
int					is_redirrect(t_list *lst, t_quote *quote);
int					parsing_redirrect(t_user *start);
int					check_redirrect(char *str, int i);
int					redirrect_error(char *elem);
int					read_redirrect(char *str, int i, t_list *lst, char *type);
int					write_redirrect(char *str, int i, t_list *lst, char *type);
char				*get_file_path(char *str, int i, t_quote *quote);
char				*get_file(char *str, int i, int j, t_quote *quote);
int					write_redirrect(char *str, int i, t_list *lst, char *type);
int					read_redirrect(char *str, int i, t_list *lst, char *type);
int					next_redirrect(char *str, int i, t_quote *q);
char				*remove_redirrect(char *str);
int					remove_redirrect_alloc(t_list *lst);
int					exec_type(int size, int old_fd[2], t_env *env, t_list *lst);
int					in_out_setup(t_fd *fds, t_list *lst);

/*
**          Environnement - Variable - $
*/

int					catch_env_varr(char *arg, char *env_line);
int					catch_env_var(char *arg, char *env_line);
int					add_environnement_var(t_list *lst, t_env *env);
char				*check_var_in_env(char *var_name, t_env *env);
int					str_check(char *str_envi, char *to_catch);
int					check_simple_quote(t_user *start, t_quote *q, int j, int i);

/*
**    Preparation a l'execution
*/

int					conditionning(t_user *start);
int					execution(t_user *start, t_env *env);
int					dispatch_cmd(t_list *lst, t_env *env);
void				check_flags(t_list *lst);
int					exec_pipe(t_list *lst, t_env *env, int size);
int					exec_execve(t_list *lst, t_env *env, char *path);
int					cmd_valididy(char *cmd, t_env *env);
int					exec_main(t_list *lst, t_env *env);
char				**get_path(char **env, char *builtin);
char				*check_path(char **paths, char *path);
void				set_gerrno(t_list *lst, t_env *env);
int					last_clean(t_list *lst);

/*
**         Built-in
*/

int					ft_cd(t_env *env, t_list *lst);
int					ft_export(t_env *env, t_list *lst);
int					ft_exit(t_env *env, t_list *lst, t_user *start);
int					ft_unset(t_env *env, t_list *lst);
int					ft_pwd(void);
int					ft_echo(t_env *env, t_list *lst);
int					ft_env(t_env *env, t_list *lst);

/*
**         Built-in utils
*/

int					check_if_exist(char **tab, char *arg);
int					check_arg_nb(char *arg);
char				**arg_to_tab(char *arg, int size, t_token_env *token);
char				**parsing_arg(char **arg_tab);
char				*first_clear_arg(char *str);
char				*clear_arg(char *str);
int					catch_env_var(char *arg, char *env_line);
char				*change_value(char *tmp, char *arg);
int					sort_export(t_env *env);
int					export_without_args(t_env *env);
int					is_valid_name(char *str);
int					is_valid_char(char c);
int					export_new_var(t_env *env, t_list *lst);
int					free_dol(t_dollar *dol, char *one, char *two);

/*
** malloc error
*/

void				malloc_error(void);

/*
** Signaux
*/

void				catch_signal(void);
void				sig_handler(int value);
int					verif_ret(int ret, char *user_input);

/*
** Debug (delete before last push)
*/

void				print_list(t_user *start);
void				debug(t_list *lst);
void				print_in_out(t_list *lst);

#endif
