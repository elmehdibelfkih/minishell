/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inpute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:55:39 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/07 21:27:51 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char *readline (const char *prompt)
void    get_line()
{
    char *line;
    char *tmp;
    
    tmp = readline ("minishell : ");
    line = ft_strtrim(tmp, " ");
    free(tmp);
    printf("%s\n ", line);
    free(line);
}

// void lex(char *line)
// {
//     char **spl_space;

//     spl_space = ft_split(line, ' ');
//     (void)spl_space;
    
// }