#include"pipex.h"

#define p printf

static void label(t_ast *node, int *id) {
  if (!node) return;

	printf("\tNode%d[label=\"",*id);

  if (node->type == PIPE_NODE) p("|");

  if (node->type == CMD_NODE) {
	p("%s",((t_cmdlist *)node)->av[0]);
  }

	p("\"]\n");
}

static void edge(int from, int to) {
	p("\tNode%d -> Node%d[wieght=10]\n",from,to);
}

static int dfs(t_ast *tree, int *id) {
  int my_id = 0, l, r;

  my_id = (*id)++;

  if (tree) {
    label(tree, &my_id);
    if (tree->type == PIPE_NODE) {
      l = dfs(((t_pipeline *)tree)->left, id);
      r = dfs(((t_pipeline *)tree)->right, id);
      edge(my_id, l);
      edge(my_id, r);
    }
  }

  return my_id;
}

void dump_dot(t_ast *tree) {
	p("digraph {\n");
  int id = 0;
  dfs(tree, &id);
  p("}\n");
}
