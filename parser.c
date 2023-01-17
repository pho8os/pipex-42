/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 11:04:59 by absaid            #+#    #+#             */
/*   Updated: 2023/01/16 22:44:45 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_ast	*pipeline_constructor(t_ast *left, t_ast *right)
{
	t_pipeline	*node;

	node = (t_pipeline *)gc(sizeof(t_pipeline), 1);
	node->type = PIPE_NODE;
	node->left = left;
	node->right = right;
	return ((t_ast *)node);
}

static t_ast	*cmdlist_constructor(char **av, size_t len)
{
	t_cmdlist	*node;

	node = (t_cmdlist *)gc(sizeof(t_cmdlist), 1);
	node->type = CMD_NODE;
	node->av = av;
	node->len = len;
	return ((t_ast *)node);
}

static t_ast	*parse_command(char *path, char *command)
{
	char	**av;
	t_ast	*cmdlist;
	size_t	len;

	len = 0;
	av = ft_split(command, 32);
	*av = get_path(path, *av);
	if (!*av)
	{
		ft_putstr_fd(command, 2);
		ft_putendl_fd(" : command not found", 2);
		return (gc(0, 0));
	}
	while (av[len])
		len++;
	cmdlist = cmdlist_constructor(av, len);
	return (cmdlist);
}

static t_ast	*parse_pipeline(char **tokens, int len, char *path)
{
	t_ast	*ret;

	if (!*tokens || !len)
		return (NULL);
	ret = parse_command(path, *tokens);
	while (*tokens++ && --len)
	{
		ret = pipeline_constructor(ret, NULL);
		((t_pipeline *)ret)->right = parse_command(path, *tokens);
	}
	return (ret);
}

t_ast	*parser(char **tokens, int len, char *path)
{
	return (parse_pipeline(tokens, len, path));
}
