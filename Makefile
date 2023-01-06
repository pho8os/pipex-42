all:
	
	cc pipex.c parser.c executor.c test.c libft.a -o pipex -g #-fsanitize=address