/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inpute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:55:39 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/10/09 21:51:08 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char *readline (const char *prompt)
void    get_line(t_list **prime)
{
    char *line;
    char *tmp;
    
    tmp = readline ("minishell : ");
    line = ft_strtrim(tmp, " ");
    free(tmp);
    disperse(line, prime);
    // printf("%s\n ", line);
    // if (check_quote(line, 0, '\''))
    //     printf("ok \n");
    // else
    //     printf("error \n");
    free(line);
}

bool check_quote(char *line, int start, char c)
{
    while (line[start])
    {
        if (line[start] == c)
        {
            start++;
            while (line[start] && line[start] != c)
                start++;
            if (line[start] == '\0')
                return false;
            // else
            // {
            //     start++;
            //     continue; // Continue checking the rest of the string.
            // }
        }
        start++;
    }
    return true;
}

void disperse(char *line, t_list **prime)
{
    int start;
    int i;
    char c;

    start = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] && (line[i] == '\'' || line[i] == '\"'))
        {
            if (start == 0)
                ft_lstadd_back(prime, ft_lstnew(ft_substr(line, start,  i - start)));
            else
                ft_lstadd_back(prime, ft_lstnew(ft_substr(line, start + 1,  i - start - 1)));
            c = line[i];
            start = i;
            i++;
            while (line[i] && line[i] != c)
                i++;
            ft_lstadd_back(prime, ft_lstnew(ft_substr(line, start, i - start + 1)));
            if (!line[i])
                return;
            start = i;
        }
        i++;
    }
    if (start == 0)
            ft_lstadd_back(prime, ft_lstnew(ft_substr(line, start,  i - start)));
    else
            ft_lstadd_back(prime, ft_lstnew(ft_substr(line, start + 1,  i - start - 1)));
}