#include"pipex.h"
static char *ft_strtok(char *s, char specifier)
{
	static char *buffer;
	char *token;

	if (!buffer)
		buffer = s;
	if (!*buffer)
		return NULL;
	token = buffer;
	while (*buffer && *buffer != specifier)
		buffer++;
	while(*buffer == specifier && *buffer)
	{
		*buffer = 0;
		buffer++;
	}		
	return(token);
}

char *get_path(char *path, char *cmd)
{
	char	*new_cmd;
	char	*token;

	if (ft_strchr(cmd,'/'))
		return cmd;
	new_cmd = ft_calloc(1, PATH_MAX);
	if (!new_cmd)
		return ((void *)0);
	token = ft_strtok(path, ':');
	while (token)
	{
		ft_strlcat(new_cmd, token, PATH_MAX);
		ft_strlcat(new_cmd, "/", PATH_MAX);
		ft_strlcat(new_cmd, cmd, PATH_MAX);
		if (!access(new_cmd, X_OK))
			return (new_cmd);
		token = ft_strtok(NULL, ':');
		new_cmd[0] = 0x0;
	}
	return (void *)0;
}
