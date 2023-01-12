#ifndef PIPEX_H_
# define PIPEX_H_

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include<fcntl.h>
#include "libft/libft.h"

#define CMD_NODE 1
#define PIPE_NODE 2

#define READ_END 0
#define WRITE_END 1

#define LEFT_SIDE 1
#define RIGHT_SIDE 2


typedef struct s_ast {
  int type;
} t_ast;

typedef struct s_cmdlist {
  int    type;
  char **av;
  size_t len;
} t_cmdlist;

typedef struct s_pipeline {
  int    type;
  t_ast *left;
  t_ast *right;
} t_pipeline;

// parser functions
t_ast *parser(char **, int, char *);

// executor functions
void executor(t_ast *,char **);

char *get_path(char *path, char *cmd);

void dump_dot(t_ast *tree);
#endif