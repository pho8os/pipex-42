#include "pipex.h"

int main()
{
	int fd[2];
	int pid;
	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[1]);
		char buff[0xff];
		int nbyte = 0;
		while ((nbyte = read(fd[0], buff, 0xff - 1)) > 0)
			write(1, buff, nbyte);
		return 0;
	}
	int file = open("pipex.h", O_RDONLY);
	int nbyte = 0;
	char buff[0xff];
	while ((nbyte = read(file, buff, 0xff - 1)) > 0)
		write(fd[1], buff, nbyte);
	close(fd[0]);
	close(fd[1]);
	close(file);
	wait(NULL);
}