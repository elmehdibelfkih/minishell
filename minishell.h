/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:01:46 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/11/09 13:45:03 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>

int	g_exit_status;

typedef enum s_component
{
	word,
	space,
	pipe_op,
	d_quote,
	s_quote,
	r_inp,
	r_out,
	here_doc,
	app_op,
	delimiter,
}	t_component;

typedef struct s_comp
{
	char			*data;
	t_component		tok;
	bool			expanded;
	int				fd;
	struct s_comp	*next;
}	t_comp;

typedef struct s_exec_info
{
	int		fd[2];
	char	*path;
	char	**envp;
	int		def_inp;
	int		def_out;
	pid_t	pid;
}	t_exec_info;

typedef struct s_redir
{
	t_component		tok;
	char			*f_name;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**cmd;
	int				inp;
	int				out;
	struct s_cmd	*next;
}	t_cmd;

void	handle_sigint(int sig);
int		execute(t_cmd **commands, t_env **env);
char	**get_paths(t_env *env, char *s);
char	*check_paths(t_cmd *command, char **paths, t_exec_info *exec_info);
char	*absolute_path(char **paths, char *cmd);
void	path_err_msg(t_cmd *command, char *cmd, char **paths);
int		check_redir(t_cmd *commands);
void	fork_err(t_exec_info *exec_info);
int		_pipe(t_exec_info *exec_info);
int		_unset(t_cmd *commands, t_env **env);
int		_cd(t_cmd *command, t_env *env);
int		__exit(t_cmd *commands);
void	ft_err_std(t_cmd *command);
void	ft_err_2(t_cmd *command);
void	ft_err_126(t_cmd *command);
void	ft_err_pd(t_cmd *command);
void	ft_err_127(t_cmd *command);
void	ft_err_pd(t_cmd *command);
void	save_fd(t_exec_info *exec_info);
void	reset_fd( t_exec_info *exec_info);
int		is_exist(char *s, int c);
int		is_end(char *s, int c);
int		is_directory(char *cmd, char **paths);
void	checker_1(t_cmd *command, char *cmd);
char	**list_to_tab(t_env *env);
int		size_env(t_env *env);
t_env	*ft_get_env(char **envp);
t_env	*ft_envnew(char *name, char *data);
t_env	*ft_envlast(t_env *lst);
t_cmd	*get_command(t_list **prime, t_comp **cmpa, t_env *env);
t_cmd	*ft_cmd_last(t_cmd *head);
t_cmd	*ft_cmdnew(char **cmd, int in_fd, int ou_fd);
t_comp	*ft_compnew(char *data, t_component	tok, bool expanded);
t_comp	*ft_comp_last(t_comp *head);
size_t	nb_cmd(t_comp *cmpa);
t_redir	*ft_redirpnew(char *f_name, int fd, t_component	tok);
t_redir	*ft_redir_last(t_redir *head);
t_redir	*redir_fill(t_comp *cmpa);
void	ft_comp_clear(t_comp **head, int i);
void	types_separation(t_list *prime, t_comp **cmpa);
void	ft_env_add_back(t_env **lst, t_env *new);
void	ft_envclear(t_env **lst);
void	env(t_env *env, t_cmd *command, int fd);
void	perr(char *str, char *str2);
void	put_export(t_env *env, int fd);
void	m_export(t_cmd *cmd, t_env **env, int fd);
void	new_data(t_env **env, char *name, char *data, bool e);
void	replace_line(t_comp *cmpa, t_env *env);
void	join_words(t_comp *cmpa);
void	ft_redir_add_back(t_redir **head, t_redir *new);
void	ft_redir_clear(t_redir **head);
void	ft_cmd_add_back(t_cmd **head, t_cmd *new);
void	ft_cmd_clear(t_cmd **head);
void	ft_comp_nd_del(t_comp **cmpa, t_comp *next);
void	trim_quotes(t_comp *cmpa);
void	delete_spaces(t_comp *cmpa);
void	here_doc_processes(t_comp *cmpa);
void	ft_comp_n_del(t_comp **cmpa, t_comp *next, bool c);
void	ft_redir_clear(t_redir **head);
void	echo(char **cmd, int fd);
char	*pwd(bool p, int fd, t_env *env);
void	here_doc_processes_assistant(t_comp **cmpa, bool	*c);
void	child_process(char *delim, bool exp, t_env *env, int *fd);
void	export_assistant(t_env **env, char *cmd, int j);
void	disperse(char *line, t_list **prime);
void	disperse_assistant(char *line, t_list **prime, int start, int i);
void	ft_comp_add_back(t_comp **head, t_comp *new);
bool	check_quotes(t_list *prime);
bool	types_separation_quotes(t_comp **cmpa, char *tmp);
bool	types_separation_pipe_space(t_comp **cmpa, char *tmp, t_list *prime);
bool	types_separation_redir_1(t_comp **cmpa, char *tmp, t_list *prime);
bool	types_separation_redir_2(t_comp **cmpa, char *tmp, t_list *prime);
bool	types_separation_word(t_comp **cmpa, char *tmp, t_list *prime);
bool	check_builtins(t_cmd *cmd, t_env **env);
bool	prs(t_list **prime, t_comp **cmpa, t_env *env);
bool	check_pipe(t_comp *cmpa, int i);
bool	cmd_struct_fill(t_comp *cmpa, t_cmd **cmd);
bool	here_doc_processes_assistant_2(t_comp **cmpa);
bool	open_here_doc(t_comp *cmpa, t_env *env);
bool	check_files(t_comp *cmpa);
bool	check_next(t_comp *cmpa);
char	*get_exp_var(char *line, t_env *env, int *j);
char	*get_env_var(char *var, t_env *env, int *j);
char	*replace_var(char *line, t_env *env, int *j);
char	*join_quotes(t_comp *cmpa, t_comp *next);
char	**cmd_fill(t_comp *cmpa);
char	*m_readline(void);
int		inp_red(t_redir	*red);
int		new_fork(char *delim, bool exp, t_env *env);
int		out_red(t_redir	*red);
int		echo_start(char **cmd, bool *s);
void	m_cd(t_cmd *cmd, t_env **env);
t_env	*o_pwd(t_env *env);
char	*join_path(char *dir, t_env *env, bool p);
bool	m_cd_assistant(char *t, char *path, t_env **env);
void	m_cd_assistant_2(char *t, char *path, t_env **env);
bool	m_cd_assistant_1(char *t, char *path, t_env **env);
void	up_date_pwd(t_env **env, char *data, bool o_p);

#endif