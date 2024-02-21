/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:27:36 by omougel           #+#    #+#             */
/*   Updated: 2024/02/21 11:28:20 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
		{
			ft_replacefront(cmd, tmp);
			return (cmd);
		}
		free(tmp);
		i++;
	}
	return (perror(str), ft_free_all("sa", tmp, cmd), NULL);
}

t_list	*fill_pipex(char **argv, char **envp)
{
	char	**env;
	t_list	*pipex;
	char	**tmp;
	size_t	i;

	pipex = NULL;
	i = 2;
	if (access(argv[1], R_OK))
		return (perror(argv[1]), NULL);
	if (access(argv[4], W_OK))
		return (perror(argv[4]), NULL);
	env = split_envp(envp);
	if (!env)
		return (NULL);
	while (i < 4)
	{
		tmp = ft_find_path(argv[i++], env);
		if (!tmp)
			return (ft_free_arr(env), NULL);
		ft_lstadd_back(&pipex, ft_lstnew(tmp));
		if (ft_lstsize(pipex) != i - 2)
			return (ft_free_all("aal", env, tmp, pipex), NULL);
	}
	return (ft_free_arr(env), pipex);
}
