/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:22:58 by omougel           #+#    #+#             */
/*   Updated: 2024/03/11 06:21:28 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**split_envp(char **envp)
{
	char	**env;
	size_t	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5))
		i++;
	if (!envp[i])
		return (ft_putstr_fd("No PATH in environement\n", 2), NULL);
	env = ft_split(&envp[i][5], ':');
	if (!env)
		return (NULL);
	return (env);
}

char	**ft_replacefront(char **cmd, char *path)
{
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
	ft_free_arr(cmd);
	return (perror(str), NULL);
}

char	**ft_nopath(char *str)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (!cmd)
		return (NULL);
	if (!access(cmd[0], X_OK))
		return (cmd);
	ft_free_arr(cmd);
	return (NULL);
}

char	**find_command(char *str, char **envp)
{
	char	**env;
	char	**cmd;

	env = split_envp(envp);
	if (!env)
		return (ft_nopath(str));
	cmd = ft_find_path(str, env);
	if (!cmd)
		return (ft_free_arr(env), NULL);
	return (ft_free_arr(env), cmd);
}
