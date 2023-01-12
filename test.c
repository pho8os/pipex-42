/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaid <absaid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 02:47:15 by absaid            #+#    #+#             */
/*   Updated: 2023/01/12 02:47:25 by absaid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"


char *get_path(char *path, char *cmd)
{
	char	*new_cmd;
	char	**token;
	int i;

	if (ft_strchr(cmd,'/'))
		return cmd;
	token = ft_split(path,':');
	new_cmd = ft_calloc(1, PATH_MAX);
	if (!new_cmd)
		return ((void *)0);
	i = -1;
	while (token[++i])
	{
		ft_strlcat(new_cmd, token[i], PATH_MAX);
		ft_strlcat(new_cmd, "/", PATH_MAX);
		ft_strlcat(new_cmd, cmd, PATH_MAX);
		if (!access(new_cmd, X_OK))
			return (new_cmd);
		free(new_cmd);
		new_cmd = ft_calloc(1, PATH_MAX);
	}
	return (NULL);

}
