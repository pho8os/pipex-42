/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:54:37 by absaid            #+#    #+#             */
/*   Updated: 2023/01/16 20:24:45 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void ff(void )
{
	system("leaks pipex");
}
char *get_path(char *path, char *cmd)
{
	char	*new_cmd;
	char	**token;
	int i;

	if(!path || !cmd)
		return(NULL);
	if (ft_strchr(cmd,'/'))
		return cmd;
	token = ft_split(path,':');
	new_cmd = ft_calloc(1, PATH_MAX);
	if (!new_cmd)
		return (gc(0,0));
	i = -1;
	while (token[++i])
	{
		ft_strlcat(new_cmd, token[i], PATH_MAX);
		ft_strlcat(new_cmd, "/", PATH_MAX);
		ft_strlcat(new_cmd, cmd, PATH_MAX);
		if (!access(new_cmd, X_OK))
			return (new_cmd);
		new_cmd = ft_calloc(1, PATH_MAX);
	}
	return (NULL);
}

int	heredoc(char *delim)
{
	int		hfd[2];
	int		len;
	char	*buff;

	if (!delim || pipe(hfd) == -1)
		return (-1);
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
	int		i;
	char	*path;

	i = -1;
	while (env[++i])
		if (env[i] && !ft_memcmp(env[i], "PATH=", 5))
			return(path = ft_strdup(env[i] + 5), path);
	return (NULL);
}

int	_main(int ac, char **av, char **env)
{
	int infile;
	int flags = O_WRONLY | O_CREAT;
	int outfile;
	t_ast *tree;

	if (ac >= 5) 
	{

		if (!strcmp(av[1], "here_doc")) 
		{
			infile = heredoc(av[2]);
			ac--, av++;
			flags |= O_APPEND;
		} 	
		else 
		{
	  		infile = open(av[1], O_RDONLY);
			if(infile < 0)
				return(perror(av[1]),0);
	  		flags |= O_TRUNC;
		}
		outfile = open(av[ac - 1], flags, 0644);
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		tree = parser(av + 2, ac - 3,pathget(env));
		// dump_dot(tree);
		executor(tree,env);
		gc(0,0);
	}
	return(0);
}

int main(int ac, char **av, char **env)
{
	_main(ac,av,env);
	while(1);
	
}