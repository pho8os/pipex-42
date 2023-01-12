all:
	
	cc pipex.c parser.c executor.c test.c dumpdot.c libft.a -o pipex -g -fsanitize=address