#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

const char *get_path(char *path, const char *cmd)
{
	char *new_cmd;

	if (strchr(cmd, '/'))
		return cmd;
	new_cmd = calloc(1, PATH_MAX);
	if (!new_cmd)
		return ((void *)0);
	char *token = strtok(path, ":");
	int step = 0;
	while (token)
	{
		strlcat(new_cmd, token, PATH_MAX);
		strlcat(new_cmd, "/", PATH_MAX);
		strlcat(new_cmd, cmd, PATH_MAX);
		if (!access(new_cmd, X_OK))
			return new_cmd;
		token = strtok(NULL, ":");
		new_cmd[0] = 0x0;
	}
	return (void *)0;
}

int main()
{
	char path[] = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";

	printf("path -> %s\n", get_path(path, "ls"));
}