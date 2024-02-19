/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:35:41 by omougel           #+#    #+#             */
/*   Updated: 2024/02/19 14:22:36 by omougel          ###   ########.fr       */
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
	free(cmd[0]);
	cmd[0] = path;
	return (cmd);
}

//MAKE A FUNCTION TO TAKE AN INFINITE NUMBER OF ARGUMENT TO FREE THEM !!!
//TAKE FT_PRINTF AS A BASE TO DO THIS ESSENTIAL FUNCTION AND THEN ADD IT TO THE LIBFT 

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
		{
			ft_replacefront(cmd, tmp);
			return (cmd);
		}
		free(tmp);
		i++;
	}
	return (perror(str), free_everything(tmp, cmd));
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
			return (ft_free_arr(env), ft_free_arr(tmp), ft_lstclear(&pipex, ft_free_arr), NULL);
	}
	return (ft_free_arr(env), pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*pipex;

	if (argc != 5)
		return (ft_putstr_fd("Invalid number of argument\n", 2), 0);
	pipex = fill_pipex(argv, envp);
	if (!pipex)
		return (0);
	ft_do_the_pipe(argv, pipex);
	return (ft_lstclear(&pipex, ft_free_arr), 0);
}
