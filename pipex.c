#include"pipex.h"

int heredoc(char *delim) {
	int         hfd[2];
	int         len;
	char *buff;

	if (!delim || pipe(hfd) == -1) return (-1);
	len = ft_strlen(delim);
	while (1) 
	{
    	buff = get_next_line(0);
    	if (!buff || ft_memcmp(delim, buff, len) == 0) 
			break;
    	write(hfd[WRITE_END], buff, ft_strlen(buff));
    	write(hfd[WRITE_END], "\n", 1);
	}
  return (close(hfd[WRITE_END]), hfd[READ_END]);
}
char *pathget(char **env)
{
	int i;
	char *path;

	i = -1;
	while(env[++i])
		if(env[i] && !ft_memcmp(env[i], "PATH=", 5))
			return(path = env[i] + 5, path);
	return (NULL);
}

int main(int ac, char **av, char **env)
{
	if (ac >= 5) 
	{

    	int infile;
    	int flags = O_WRONLY | O_CREAT;

		if (!strcmp(av[1], "here_doc")) 
		{
			infile = heredoc(av[2]);
			ac--, av++;
    		flags |= O_APPEND;
    	} 	
		else 
		{
      		infile = open(av[1], O_RDONLY);
      		flags |= O_TRUNC;
    	}
		int outfile = open(av[ac - 1], flags, 0644);
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		t_ast *tree = parser(av + 2, ac - 3,pathget(env));
		// dump_dot(tree);
		executor(tree,env);
	}
}