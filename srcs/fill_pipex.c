/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:27:36 by omougel           #+#    #+#             */
/*   Updated: 2024/02/26 13:04:46 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdlib.h>

char	**split_envp(char **envp)
{
	char	**env;
	size_t	i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		i++;
	env = ft_split(&envp[i][5], ':');
	if (!env)
		return (NULL);
	return (env);
}

char	**ft_replacefront(char **cmd, char *path)
{
	size_t	i;

	i = 0;
	free(cmd[0]);
	cmd[0] = path;
	return (cmd);
}

char	**ft_find_path(char *str, char **env)
{
	size_t	i;
	char	*tmp;
	char	**cmd;

	i = 0;
	cmd = ft_split(str, ' ');
	if (!cmd)
		return (NULL);
	while (env[i])
	{
		tmp = ft_strjoin(env[i], cmd[0]);
		if (!tmp)
			return (ft_free_arr(cmd), NULL);
		if (!access(tmp, X_OK))
			return (ft_replacefront(cmd, tmp));
		free(tmp);
		i++;
	}
	return (perror(str), free(tmp), ft_replacefront(cmd, NULL));
}

void	free2arr(char **arr1, char **arr2)
{
	ft_free_arr(arr1);
	ft_free_arr(arr2);
}

t_list	*fill_pipex(char **argv, char **envp)
{
	char	**env;
	t_list	*pipex;
	char	**tmp;
	size_t	i;

	pipex = NULL;
	i = 2;
	env = split_envp(envp);
	if (!env)
		return (NULL);
	while (i < 4)
	{
		tmp = ft_find_path(argv[i++], env);
		if (!tmp)
			return (ft_free_arr(env), ft_lstclear(&pipex, ft_free_arr), NULL);
		if (!tmp[0])
			ft_free_arr(tmp);
		ft_lstadd_back(&pipex, ft_lstnew(tmp));
		if (ft_lstsize(pipex) != i - 2)
			return (free2arr(env, tmp), free(pipex), NULL);
	}
	return (ft_free_arr(env), pipex);
}
