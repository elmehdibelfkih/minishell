# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/21 09:52:57 by ebelfkih          #+#    #+#              #
#    Updated: 2023/10/05 22:31:53 by ebelfkih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MANDATORY_PART = ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c\
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_strlen.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcmp.c \
			ft_strlcpy.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_putstr_fd.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_strtrim.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_itoa.c \
			ft_strlcat.c \
			ft_split.c \

BONUS_PART = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \

NAME = libft.a

CC = cc -Wall -Werror -Wextra

AR = ar rc

RM = rm -f

MANDATORY_O = $(MANDATORY_PART:.c=.o)

BONUS_O = $(BONUS_PART:.c=.o)


all: $(NAME)

%.o:%.c libft.h
	$(CC) -o $@ -c $<
	
$(NAME) : $(MANDATORY_O)
	$(AR) $(NAME) $(MANDATORY_O)

bonus: $(BONUS_O)
	$(AR) $(NAME) $(BONUS_O)


clean:
	$(RM) $(BONUS_O)  $(MANDATORY_O)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY = clean fclean bonus
