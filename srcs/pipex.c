/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:35:41 by omougel           #+#    #+#             */
/*   Updated: 2024/02/15 17:15:20 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**split_envp(char **envp)
{
	char	**env;
	char	*tmp;
	size_t	i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		i++;
	tmp = ft_strtrim(envp[i], "PATH=");
	if (!tmp)
		return (ft_putstr_fd("malloc failed\n", 2), NULL);
	env = ft_split(tmp, ':');
	if (!env)
		return (free(tmp), ft_putstr_fd("malloc failed\n", 2), NULL);
	free(tmp);
	return (env);
}

char	*ft_find_path(char *str, char **env)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_strjoin(env[i], ft_split(str, ' ')[0]);
		if (!access(tmp, X_OK))
			return (tmp);
		i++;
	}
	return (free(tmp), perror(str), NULL);
}

t_list	**fill_pipex(char **argv, char **envp)
{
	char	**env;
	t_list	**pipex;
	char	*tmp;
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
