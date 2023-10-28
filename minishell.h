/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:01:46 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/28 16:47:06 by ybouchra         ###   ########.fr       */
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

int	exit_status;

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

void	execute(t_cmd **commands, t_env **env);
char	**get_paths(t_env *env, char *s);
char	*find_path(char **paths, char *cmd);
int		check_paths(t_cmd *command, char **paths, t_exec_info *exec_info);
void	ft_err(t_cmd *command);
int		_env(t_cmd *commands, t_env *env);
int		_unset(t_cmd *commands, t_env *env);
void    save_fd(t_exec_info *exec_info);
void	reset_fd( t_exec_info *exec_info);
char	**list_to_tab(t_env *env);//ussef
t_env	*ft_get_env(char **envp); // mehdi
t_env	*ft_envnew(char *name, char *data); // mehdi
t_env	*ft_envlast(t_env *lst); // mehdi
t_cmd	*get_command(t_list **prime, t_comp **cmpa, t_env *env); // mehdi
t_cmd	*ft_cmd_last(t_cmd *head); // mehdi
t_cmd	*ft_cmdnew(char **cmd, int in_fd, int ou_fd); // mehdi
t_comp	*ft_compnew(char *data, t_component	tok, bool expanded); // mehdi
t_comp	*ft_comp_last(t_comp *head); // mehdi
size_t	nb_cmd(t_comp *cmpa); // mehdi
t_redir	*ft_redirpnew(char *f_name, int fd, t_component	tok); // mehdi
t_redir	*ft_redir_last(t_redir *head); // mehdi
t_redir	*redir_fill(t_comp *cmpa); // mehdi
void	ft_comp_clear(t_comp **head, int i); // mehdi
void	types_separation(t_list *prime, t_comp **cmpa); // mehdi
void	ft_env_add_back(t_env **lst, t_env *new); // mehdi
void	ft_envclear(t_env **lst); // mehdi
void	env(t_env *env, int fd); // mehdi
void	perr(char *str, char *str2); // mehdi
void	put_export(t_env *env, int fd); // mehdi
void	m_export(t_cmd *cmd, t_env **env, int fd); // mehdi
void	new_data(t_env **env, char *name, char *data, bool e); // mehdi
void	replace_line(t_comp *cmpa, t_env *env); // mehdi
void	join_words(t_comp *cmpa); // mehdi
void	ft_redir_add_back(t_redir **head, t_redir *new); // mehdi
void	ft_redir_clear(t_redir **head); // mehdi
void	ft_cmd_add_back(t_cmd **head, t_cmd *new); // mehdi
void	ft_cmd_clear(t_cmd **head); // mehdi
void	ft_comp_nd_del(t_comp **cmpa, t_comp *next); // mehdi
void	trim_quotes(t_comp *cmpa); // mehdi
void	delete_spaces(t_comp *cmpa); //mehdi
void	here_doc_processes(t_comp *cmpa); // mehdi
void	ft_comp_n_del(t_comp **cmpa, t_comp *next, bool c); // mehdi
void	ft_redir_clear(t_redir **head); // mehdi
void	echo(char **cmd, int fd); // mehdi
void	pwd(int fd); // mehdi
void	here_doc_processes_assistant(t_comp **cmpa, bool	*c); // mehdi
void	child_process(char *delim, bool exp, t_env *env, int *fd); // mehdi
void	export_assistant(t_env **env, char *cmd, int j); // mehdi
void	disperse(char *line, t_list **prime); // mehdi
void	disperse_assistant(char *line, t_list **prime, int start, int i); //mehdi
void	ft_comp_add_back(t_comp **head, t_comp *new); // mehdi
bool	check_quotes(t_list *prime); // mehdi
bool	types_separation_quotes(t_comp **cmpa, char *tmp); //mehdi
bool	types_separation_pipe_space(t_comp **cmpa, char *tmp, t_list *prime); // mehdi
bool	types_separation_redirections_1(t_comp **cmpa, char *tmp, t_list *prime); // mehdi
bool	types_separation_redirections_2(t_comp **cmpa, char *tmp, t_list *prime); //mehdi
bool	types_separation_word(t_comp **cmpa, char *tmp, t_list *prime); // mehdi
bool	check_builtins(t_cmd *cmd, t_env **env); // mehdi
bool	prs(t_list **prime, t_comp **cmpa, t_env *env); // mehdi
bool	check_pipe(t_comp *cmpa, int i); // mehdi
bool	cmd_struct_fill(t_comp *cmpa, t_cmd **cmd); // mehdi
bool	here_doc_processes_assistant_2(t_comp **cmpa); // mehdi
bool	open_here_doc(t_comp *cmpa, t_env *env); // mehdi
bool	check_files(t_comp *cmpa); // mehdi
bool	check_next(t_comp *cmpa); // mehdi
char	*get_exp_var(char *line, t_env *env, int *j); //mehdi
char	*get_env_var(char *var, t_env *env, int *j); // mehdi
char	*replace_var(char *line, t_env *env, int *j); // mehdi
char	*join_quotes(t_comp *cmpa, t_comp *next); // mehdi
char	**cmd_fill(t_comp *cmpa); // mehdi
char	*m_readline(void); //mehdi
int		inp_red(t_redir	*red); // mehdi
int		new_fork(char *delim, bool exp, t_env *env); // mehdi
int		out_red(t_redir	*red); // mehdi
int		echo_start(char **cmd, bool *s); // mehdi

#endif