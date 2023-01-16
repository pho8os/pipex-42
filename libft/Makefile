# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: absaid <absaid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 07:27:30 by absaid            #+#    #+#              #
#    Updated: 2023/01/16 18:45:33 by absaid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS =  ft_putendl_fd.c ft_putstr_fd.c ft_memcmp.c\
	ft_split.c  ft_strdup.c ft_strchr.c ft_bzero.c ft_memset.c\
	ft_strlcat.c ft_strlcpy.c ft_strlen.c  ft_calloc.c\
 	ft_substr.c  get_next_line.c get_next_line_utils.c gc.c\

BONUS =  ft_lstnew.c  ft_lstadd_back.c ft_lstclear.c


BONUSOBJS = $(BONUS:.c=.o)

OBJS = $(SRCS:.c=.o)

all:$(NAME)

%.o:%.c libft.h get_next_line.h
	$(CC) $(CFLAGS) -c $<

bonus : $(BONUSOBJS) $(NAME)
	ar cr $(NAME) $(BONUSOBJS) 	

$(NAME):$(OBJS)
	ar cr $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(BONUSOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all