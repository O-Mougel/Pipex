/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_the_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:38:45 by omougel           #+#    #+#             */
/*   Updated: 2024/02/26 14:35:56 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define O_FILE_2 1101 //O_WRONLY O_TRUNC O_CREATE

void	ft_close_all(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
/*
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
	close(file_fd);
	close(fd[0]);
	close(fd[1]);
	execve(cmd[0], cmd, envp);
}

void	exec_second_pipe(char *file2, int *fd, char **cmd, char **envp)
{
	int	file_fd;

	file_fd = open(file2, O_WRONLY|O_TRUNC|O_CREAT);
	if (file_fd < 0)
		return ;
	if (dup2(file_fd, STDOUT_FILENO) < 0)
		return ;
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return ;
	close(file_fd);
	close(fd[0]);
	close(fd[1]);
	execve(cmd[0], cmd, envp);
}
*/

void	ft_exit(void)
{
	perror(NULL);
	exit(errno);
}

void	ft_exec_pipe(int fd_in, int fd_out, char **cmd, char **envp)
{
	if (fd_in < 0 || fd_out < 0)
		ft_exit();
	if (dup2(fd_in, STDIN_FILENO) < 0)
		ft_exit();
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		ft_exit();
	ft_close_all(fd_in, fd_out);
	if (cmd && *cmd)
		execve(cmd[0], cmd, envp);
	ft_exit();
}

void	ft_do_the_pipe(char **argv, t_list *pipex, int *fd, char **envp)
{
	int	pid1;
	int	pid2;
	int err1;
	int err2;

	pid1 = -1;
	pid2 = -1;
	err1 = -1;
	err2 = -1;
	if (!access(argv[1], R_OK) && pipex->content)
	{
		pid1 = fork();
		if (pid1 < 0)
			return (perror(NULL), ft_close_all(fd[0], fd[1]));
		if (pid1 == 0)
		{
		//	exec_first_pipe(argv[1], fd, pipex->content, envp);
			close(fd[0]);
			ft_exec_pipe(open(argv[1], O_RDONLY), fd[1], pipex->content, envp);
		}
	}
	pipex = pipex->next;
	if (!access(argv[4], W_OK) && pipex->content)
	{
		pid2 = fork();
		if (pid2 < 0)
			return (ft_close_all(fd[0], fd[1]));
		if (pid2 == 0)
		{
		//	exec_second_pipe(argv[4], fd, pipex->content, envp);
			close(fd[1]);
			ft_exec_pipe(fd[0], open(argv[4], 577), pipex->content, envp);
		}
	}
	close(fd[0]);
	close(fd[1]);
	if (pid1 >= 0)
		waitpid(pid1, &err1, 0);
	if (pid2 >= 0)
		waitpid(pid2, &err2, 0);
}
