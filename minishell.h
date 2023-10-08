/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:01:46 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/07 21:45:32 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <stdint.h>
# include <limits.h>
# include <stdint.h>


# define NO_INP -3
# define NO_OUT -3
# define FSIGNAL 128

typedef enum s_component
{
    word,
    space,
    pipee,
    double_quote,
    single_quote,
    redirect_input, //<
    redirect_output, //>
    here_doc, // <<
    append_operator, // >>
} t_component;


typedef enum e_tok
{
	WRD = word,
	SPA = space,
	DQU = double_quote,
	SQU = single_quote,
	INP = redirect_input,
	OUT = redirect_output,
	HER = here_doc,
	APP = append_operator,
	PIP = pipee,
}	t_tok;


typedef struct s_lex
{
	t_component		tok;
	char			*data;
	bool			expanded;
	struct s_lex	*next;
}	t_lex;



typedef struct s_redir
{
	t_component		type;
	char			*file;
	int				flag;
	int				fd;
	struct s_redir	*next;
}	t_redir;

// env list
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

void	execute(t_cmd **commands, t_env **env); //ussef
t_env	*ft_get_env(char **envp); // mehdi
t_env	*ft_envnew(char *name, char *data); // mehdi
void	ft_env_add_back(t_env **lst, t_env *new); // mehdi
t_env	*ft_envlast(t_env *lst); // mehdi
void	ft_envclear(t_env **lst); // mehdi
void    get_line(); // mehdi

#endif