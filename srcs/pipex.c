/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:35:41 by omougel           #+#    #+#             */
/*   Updated: 2024/03/04 09:43:45 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*pipex;
	int		fd[2];
	int		success;

	if (argc != 5)
		return (ft_putstr_fd("Invalid number of argument\n", 2), 1);
	if (pipe(fd) == -1)
		return (perror(NULL), 1);
	pipex = fill_pipex(argv, envp);
	if (!pipex)
		return (1);
	success = ft_do_the_pipe(argv, pipex, fd, envp);
	if (success)
		return (ft_lstclear(&pipex, ft_free_arr), 1);
	return (ft_lstclear(&pipex, ft_free_arr), 0);
}
