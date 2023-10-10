/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:01:46 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/10 22:07:15 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
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

typedef enum s_component
{
    word,
    space,
    pipe,
    double_quote,
    single_quote,
    redirect_input, // <
    redirect_output, // >
    here_doc, // <<
    append_operator, // >>
} t_component;


typedef struct s_comp
{
	char			*data;
	t_component		tok;
	bool			expanded;
	struct s_comp	*next;
}	t_comp;



typedef struct s_redir
{
	t_component		type;
	char			*file;
	int				flag;
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
	t_redir			*redir;
	int				inp;
	int				out;
	struct s_cmd	*next;
}	t_cmd;

t_env	*ft_get_env(char **envp); // mehdi
t_env	*ft_envnew(char *name, char *data); // mehdi
void	ft_env_add_back(t_env **lst, t_env *new); // mehdi
t_env	*ft_envlast(t_env *lst); // mehdi
void	ft_envclear(t_env **lst); // mehdi
void	get_line(t_list **prime); // mehdi
void	disperse(char *line, t_list **prime); // mehdi
bool	check_quotes(t_list *prime); // mehdi
void	disperse_assistant(char *line, t_list **prime, int start, int i); //mehdi
t_comp	*ft_compnew(char *data, t_component	tok, bool expanded); // mehdi
void	ft_comp_add_back(t_comp **head, t_comp *new); // mehdi
t_comp	*ft_comp_last(t_comp *head); // mehdi
void	ft_comp_clear(t_comp **head); // mehdi
void    types_separation(t_list *prime, t_comp *cmpa); // mehdi
bool	types_separation_quotes(t_comp *cmpa, char *tmp); //mehdi
bool	types_separation_pipe_space(t_comp *cmpa, char *tmp, t_list *prime); // mehdi

#endif