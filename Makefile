# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 23:01:54 by ebelfkih          #+#    #+#              #
#    Updated: 2023/11/09 15:48:15 by ebelfkih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC   = CC -Wall -Wextra -Werror -I ~/homebrew/Cellar/readline/8.2.1/include #-fsanitize=address -g 
SRC  = libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_isprint.c libft/ft_toupper.c libft/ft_tolower.c \
libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memchr.c libft/ft_strlen.c libft/ft_strchr.c libft/ft_strrchr.c libft/ft_strnstr.c libft/ft_strncmp.c \
libft/ft_atoi.c libft/ft_memset.c libft/ft_bzero.c libft/ft_memcmp.c libft/ft_strlcpy.c libft/ft_calloc.c libft/ft_strdup.c libft/ft_substr.c \
libft/ft_strjoin.c libft/ft_putstr_fd.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_strtrim.c libft/ft_strmapi.c \
libft/ft_striteri.c libft/ft_itoa.c libft/ft_strlcat.c libft/ft_split.c  libft/ft_lstnew.c libft/ft_lstadd_front.c libft/ft_lstsize.c \
libft/ft_lstlast.c libft/ft_lstadd_back.c libft/ft_lstdelone.c libft/ft_lstclear.c libft/ft_lstiter.c libft/ft_lstmap.c \
parsing/get_env.c parsing/read_inpute.c parsing/input_structuring.c parsing/input_structuring_2.c parsing/check_syntax.c parsing/quotes_processes.c \
parsing/here_doc_processes.c parsing/get_final_struct.c parsing/redirections.c parsing/redirections_2.c \
parsing/get_final_struct.c parsing/get_final_struct_2.c parsing/check.c parsing/expand_processes.c \
builtins/echo_pwd_env.c parsing/export.c  \
execution/exec_utils.c execution/execute.c builtins/cd.c builtins/_exit.c builtins/_unset.c execution/exec_utils1.c execution/exec_utils2.c execution/exec_utils3.c execution/ft_errs.c main.c 

INC  =  libft/libft.h minishell.h
RM   = rm -f
OBJ  = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -lreadline -L"/Users/$(USER)/homebrew/Cellar/readline/8.2.1/lib" -o $@

%.o: %.c $(INC)
	$(CC) -c $<  -o $@

clean:
	$(RM) $(OBJ)


fclean: clean
	$(RM) $(NAME)

re: fclean all
