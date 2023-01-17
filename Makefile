
NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS = pipex.c parser.c executor.c dumpdot.c

OBJS = $(SRCS:.c=.o)

all:$(NAME)

libft/libft.a:
	make bonus -C libft

%.o:%.c pipex.h libft/libft.h 
	$(CC) $(CFLAGS) -c $<

$(NAME):$(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME) 

clean:
	rm -f $(OBJS) $(BONUSOBJS)
	make clean -C libft

fclean: clean 
	rm -f $(NAME)
	make fclean -C libft

re: fclean all 

.PHONY: clean fclean re all
