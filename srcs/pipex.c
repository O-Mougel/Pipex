/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:35:41 by omougel           #+#    #+#             */
/*   Updated: 2024/02/16 15:26:22 by omougel          ###   ########.fr       */
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
		return (ft_putstr_fd("malloc failed\n", 2), NULL);
	return (env);
}

char	**ft_replacefront(char **cmd, char *path)
{
	free(cmd[0]);
	cmd[0] = path;
	return (cmd);
}

char	**free_everything(char *str, char **tab)
{
	free(str);
	ft_free_arr(tab);
	return (NULL);
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
		i++;
	}
	return (perror(str), free_everything(tmp, cmd));
}

t_list	**fill_pipex(char **argv, char **envp)
{
	char	**env;
	t_list	**pipex;
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
		return (ft_putstr_fd("malloc failed\n", 2), NULL);
	while (i < 4)
	{
		tmp = ft_find_path(argv[i++], env);
		if (!tmp)

		ft_lstadd_back(pipex, ft_lstnew(&tmp));
	}
	return (ft_free_arr(env), pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_list **pipex;
	int i;

	i = 0;
	if (argc != 5)
 		return (ft_putstr_fd("Invalid number of argument\n", 2), 0);
	pipex = fill_pipex(argv, envp);
	if (!pipex)
		return (perror(NULL), 0);
	while (envp[i])
		ft_printf("%s\n",envp[i++]);
	return (ft_lstclear(pipex, ft_free_arr), 0);
}
