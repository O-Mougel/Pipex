/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:35:41 by omougel           #+#    #+#             */
/*   Updated: 2024/02/22 19:08:26 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*pipex;
	int		fd[2];

	if (argc != 5)
		return (ft_putstr_fd("Invalid number of argument\n", 2), 0);
	if (pipe(fd) == -1)
		return (perror(NULL), 0);
	pipex = fill_pipex(argv, envp);
	if (!pipex)
		return (0);
	ft_do_the_pipe(argv, pipex, fd, envp);
	return (ft_lstclear(&pipex, ft_free_arr), 0);
}
