#include"pipex.h"
int	fileopen(char *file, int des)
{
	if (des)
	{
		if (access(file, F_OK))
		{
			write(2, file, ft_strlen(file));
			write(2, ": No such file or directory\n", 28);
			return (0);
		}
		return (open(file,O_RDONLY));
	}
	return (open(file, O_CREAT | O_WRONLY));
}

const char *get_path(char *path, const char *cmd)
{
	char	*new_cmd;
	char	*token;

	if (ft_strchr(cmd,'/'))
		return cmd;
	new_cmd = ft_calloc(1, PATH_MAX);
	if (!new_cmd)
		return ((void *)0);
	token = ft_strtok(path, ":");
	while (token)
	{
		ft_strlcat(new_cmd, token, PATH_MAX);
		ft_strlcat(new_cmd, "/", PATH_MAX);
		ft_strlcat(new_cmd, cmd, PATH_MAX);
		if (!access(new_cmd, X_OK))
			return new_cmd;
		token = ft_strtok(NULL, ":");
		new_cmd[0] = 0x0;
	}
	return (void *)0;
}

int	main(int ac, char **av, char **env)
{	
	if(ac >= 5)
	{
		int fdin = fileopen(av[1], 0);
		int fdout = fileopen(av[ac - 1],1);
	}
}
