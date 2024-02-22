/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_the_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:38:45 by omougel           #+#    #+#             */
/*   Updated: 2024/02/22 19:08:22 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <fcntl.h>
#include <unistd.h>

#define O_FILE_2 1101 //O_WRONLY O_TRUNC O_CREATE

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

	file_fd = open(file2, O_WRONLY);// O_TRUNC O_CREATE);
	if (file_fd < 0)
		return ;
	if (dup2(file_fd, STDOUT_FILENO) < 0)
		return ;
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return ;
	ft_close_all(file_fd, fd);
	execve(cmd[0], cmd, envp);
}

void	ft_exec_pipe(int fd_in, int fd_out, char **cmd, char **envp)
{
	if (fd_in < 0 || fd_out < 0)
		return ;
	if (dup2(fd_in, STDIN_FILENO) < 0)
		return ;
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		return ;
	ft_close_all(fd_in, fd_out);
	execve(cmd[0], cmd, envp);
	exit(EXIT_FAILURE);
}

void	ft_do_the_pipe(char **argv, t_list *pipex, char **envp, int *fd)
{
	int	pid1;
	int	pid2;

	if (!access(argv[1], R_OK) && pipex->content)
	{
		pid1 = fork();
		if (pid1 < 0)
			return (perror(NULL), ft_close_all(-1, fd));
		if (pid1 == 0)
		{
			close(fd[0]);
			ft_exec_pipe(open(argv[1], O_RDONLY), fd[1], pipex->content, envp);
		}
	}
	pipex = pipex->next;
	if (!access(argv[4], W_OK) && pipex->content)
	{
		pid2 = fork();
		if (pid2 < 0)
			return (ft_close_all(-1, fd));
		if (pid2 == 0)
			ft_exec_pipe(open(argv[4], O_FILE_2), fd[0], pipex->content, envp);
	}
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
