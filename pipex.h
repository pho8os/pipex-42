/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:37:08 by absaid            #+#    #+#             */
/*   Updated: 2023/01/17 22:03:50 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

# define CMD_NODE 1
# define PIPE_NODE 2
# define READ_END 0
# define WRITE_END 1
# define LEFT_SIDE 1
# define RIGHT_SIDE 2

typedef struct s_ast
{
	int	type;
}	t_ast;
typedef struct s_cmdlist
{
	int		type;
	char	**av;
	size_t	len;
}	t_cmdlist;
typedef struct s_pipeline
{
	int		type;
	t_ast	*left;
	t_ast	*right;
}	t_pipeline;
typedef struct s_main
{
	int		infile;
	int		flags;
	int		outfile;
	t_ast	*tree;
}	t_main;
t_ast	*parser(char **tokens, int len, char *path);
void	executor(t_ast *tree, char **env);
char	*get_path(char *path, char *cmd);
void	dump_dot(t_ast *tree);
#endif