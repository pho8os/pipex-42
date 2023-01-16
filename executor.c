/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:34:03 by absaid            #+#    #+#             */
/*   Updated: 2023/01/16 01:18:51 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static void run_cmd(t_cmdlist *cmdlist, char **env)
{
	int pid;
	
	pid = fork();
	if(pid == -1)
		return ;
	else if(!pid)
	{
		execve(cmdlist->av[0],cmdlist->av,env);
		perror("execve");
		exit(1);
	}
	waitpid(pid, NULL, 0);
}

static void close_pipe(int fds[2])
{
	close(fds[READ_END]);
	close(fds[WRITE_END]);
}


static pid_t	run_pipe(t_ast *pipeline, int fds[2], int side, char **env)
{
	pid_t	pid;
	int		end;
	int		fileno;
	
	end = WRITE_END;
	fileno = STDOUT_FILENO;
	if(side == RIGHT_SIDE)
	{
		end = READ_END;
		fileno = STDIN_FILENO;
	}
	pid = fork();
	if(!pid)
	{
		dup2(fds[end],fileno);
		close_pipe(fds);
		executor(pipeline,env);
		exit(1);
	}
	return(pid);
}

static void run_pipeline(t_pipeline *pipleine, char **env) 
{
	int pids[2];
	int fds[2];

	if (pipe(fds) == -1)
		return;
	pids[0] = run_pipe(pipleine->left, fds, LEFT_SIDE, env);
	if (pids[0] == -1)
		return;
	pids[1] = run_pipe(pipleine->right, fds, RIGHT_SIDE, env);
	if (pids[1] == -1)
		return;
	close_pipe(fds);
	wait(NULL);
	wait(NULL);
}

void executor(t_ast *tree, char **env) 
{
	if (!tree) 
		return;
	if (tree->type == CMD_NODE) 
		run_cmd((t_cmdlist *)tree,env);
	if (tree->type == PIPE_NODE) 
		run_pipeline((t_pipeline *)tree, env);
}