/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_the_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:38:45 by omougel           #+#    #+#             */
/*   Updated: 2024/02/21 15:37:42 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

void	ft_close_all(int file_fd, int *fd)
{
	if (file_fd > 0)
		close(file_fd);
	close(fd[0]);
	close(fd[1]);
}

void	exec_first_pipe(char *file1, int *fd, char **cmd, char **envp)
{
	int	file_fd;

	file_fd = open(file1, O_RDONLY);
	if (file_fd < 0)
		return ;
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		return ;
	if (dup2(file_fd, STDIN_FILENO) < 0)
		return ;
	ft_close_all(file_fd, fd);
	execve(cmd[0], cmd, envp);
}

void	exec_second_pipe(char *file2, int *fd, char **cmd, char **envp)
{
	int	file_fd;

	file_fd = open(file2, O_WRONLY O_TRUNC O_CREATE);
	if (file_fd < 0)
		return ;
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return ;
	if (dup2(file_fd, STDOUT_FILENO) < 0)
		return ;
	ft_close_all(file_fd, fd);
	execve(cmd[0], cmd, envp);
}

void	ft_do_the_pipe(char **argv, t_list *pipex, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (perror(NULL));
	pid1 = fork();
	if (pid1 < 0)
		return (perror(NULL), ft_close_all(-1, fd));
	if (pid1 == 0)
		exec_first_pipe(argv[1], fd, pipex->content, envp);
	pipex = pipex->next;
	pid2 = fork();
	if (pid2 < 0)
		return (ft_close_all(-1, fd));
	if (pid2 == 0)
		exec_second_pipe(argv[4], fd, pipex->content, envp);
	ft_close_all(-1, fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
