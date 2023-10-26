/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:01:46 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/26 07:38:37 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <unistd.h>
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
int		check_path(char *path);
char	*find_path(char **paths, char *cmd);
char	**get_paths(t_env *env, char *s);
void	ft_err(t_cmd *command);//ussef
t_env	*ft_get_env(char **envp);
t_env	*ft_envnew(char *name, char *data);
t_env	*ft_envlast(t_env *lst);
t_comp	*ft_compnew(char *data, t_component	tok, bool expanded);
t_comp	*ft_comp_last(t_comp *head);
void	ft_env_add_back(t_env **lst, t_env *new);
void	ft_envclear(t_env **lst);
t_cmd	*get_command(t_list **prime, t_comp **cmpa, t_env *env);
void	disperse(char *line, t_list **prime);
bool	check_quotes(t_list *prime);
void	disperse_assistant(char *line, t_list **prime, int start, int i);
void	ft_comp_add_back(t_comp **head, t_comp *new);
void	ft_comp_clear(t_comp **head, int i);
void	types_separation(t_list *prime, t_comp **cmpa);
bool	types_separation_quotes(t_comp **cmpa, char *tmp);
bool	types_separation_pipe_space(t_comp **cmpa, char *tmp, t_list *prime);
bool	types_separation_redirections_1(t_comp **cmpa, char *tmp, t_list *prime);
bool	types_separation_redirections_2(t_comp **cmpa, char *tmp, t_list *prime);
bool	types_separation_word(t_comp **cmpa, char *tmp, t_list *prime);
bool	check_files(t_comp *cmpa);
bool	check_next(t_comp *cmpa);
void	here_doc_processes(t_comp *cmpa);
void	ft_comp_n_del(t_comp **cmpa, t_comp *next, bool c);
char	*get_exp_var(char *line, t_env *env, int *j);
char	*get_env_var(char *var, t_env *env, int *j);
char	*replace_var(char *line, t_env *env, int *j);
void	replace_line(t_comp *cmpa, t_env *env);
void	join_words(t_comp *cmpa);
void	ft_comp_nd_del(t_comp **cmpa, t_comp *next);
void	trim_quotes(t_comp *cmpa);
void	delete_spaces(t_comp *cmpa);
char	*join_quotes(t_comp *cmpa, t_comp *next);
void	here_doc_processes_assistant(t_comp **cmpa, bool	*c);
bool	here_doc_processes_assistant_2(t_comp **cmpa);
bool	open_here_doc(t_comp *cmpa, t_env *env);
int		new_fork(char *delim, bool exp, t_env *env);
void	child_process(char *delim, bool exp, t_env *env, int *fd);
void	exit_message(int i);
bool	prs(t_list **prime, t_comp **cmpa, t_env *env);
bool	check_pipe(t_comp *cmpa, int i);
t_redir	*ft_redirpnew(char *f_name, int fd, t_component	tok);
void	ft_redir_add_back(t_redir **head, t_redir *new);
t_redir	*ft_redir_last(t_redir *head);
void	ft_redir_clear(t_redir **head);
t_redir	*redir_fill(t_comp *cmpa);
t_cmd	*ft_cmdnew(char **cmd, int in_fd, int ou_fd);
void	ft_cmd_add_back(t_cmd **head, t_cmd *new);
t_cmd	*ft_cmd_last(t_cmd *head);
void	ft_cmd_clear(t_cmd **head);
size_t	nb_cmd(t_comp *cmpa);
int		inp_red(t_redir	*red);
int		out_red(t_redir	*red);
char	**cmd_fill(t_comp *cmpa);
bool	cmd_struct_fill(t_comp *cmpa, t_cmd **cmd);
void	ft_redir_clear(t_redir **head);
char	*m_readline(void);
#endif