/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_the_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:38:45 by omougel           #+#    #+#             */
/*   Updated: 2024/03/04 10:18:09 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

void	first_pipe(int *fd, char *file1, char **cmd, char **envp)
{
	close(fd[0]);
	if (!access(file1, R_OK) && cmd)
		ft_exec_pipe(open(file1, O_RDONLY), fd[1], cmd, envp);
	close(fd[1]);
	ft_exit();
}

void	second_pipe(int *fd, char *file2, char **cmd, char **envp)
{
	close(fd[1]);
	if (!access(file2, W_OK) && cmd)
		ft_exec_pipe(fd[0], open(file2, 577), cmd, envp);
	close(fd[1]);
	ft_exit();
}

int	ft_do_the_pipe(char **argv, t_list *pipex, int *fd, char **envp)
{
	int	pid1;
	int	pid2;
	int	err1;
	int	err2;

	pid1 = fork();
	if (pid1 < 0)
		return (perror(NULL), ft_close_all(fd[0], fd[1]), errno);
	if (pid1 == 0)
		first_pipe(fd, argv[1], pipex->content, envp);
	pipex = pipex->next;
	pid2 = fork();
	if (pid2 < 0)
		return (perror(NULL), ft_close_all(fd[0], fd[1]), errno);
	if (pid2 == 0)
		second_pipe(fd, argv[4], pipex->content, envp);
	ft_close_all(fd[0], fd[1]);
	waitpid(pid1, &err1, 0);
	waitpid(pid2, &err2, 0);
	return (err1 || err2);
}
