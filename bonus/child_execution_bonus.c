/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:26:09 by omougel           #+#    #+#             */
/*   Updated: 2024/03/07 16:57:38 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>

void	ft_exit(void)
{
	perror(NULL);
	exit(errno);
}

void	exec_command(char *str, int fd_in, int fd_out, char **envp)
{
	char			**cmd;

	cmd = find_command(str, envp);
	if (cmd && *cmd)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			ft_exit();
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			ft_exit();
		close(fd_in);
		close(fd_out);
		execve(cmd[0], cmd, envp);
	}
	else 
	{
		close(fd_in);
		close(fd_out);
	}
	ft_free_arr(cmd);
	exit(errno);
}

void	pipex(int *fd_in, char **argv, char **envp, char *str)
{
	int				fd[2];
	int				pid;

	if (pipe(fd) == -1)
		return (perror(NULL));
	if (*fd_in == 0)
		*fd_in = open(argv[1], O_RDONLY, 0644);
	if (*fd_in > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			exec_command(str, *fd_in, fd[1], envp);
		}
	}
	if (*fd_in < 0)
		perror(argv[1]);
	close(fd[1]);
	close(*fd_in);
	*fd_in = fd[0];
}

int	last_child(int fd_in, char **argv, char **envp, int argc)
{
	int	fd_out;
	int	pid;

	fd_out = open(argv[argc - 1], 577, 0644);
	pid = -1;
	if (fd_out > 0)
	{
		pid = fork();
		if (pid == 0)
			exec_command(argv[argc - 2], fd_in, fd_out, envp);
	}
	close(fd_in);
	close(fd_out);
	if (fd_out > 0)
		return (pid);
	return (perror(argv[argc - 1]), -1);
}

int	wait_all_child(int last_child, int number_of_childs)
{
	int	status;

	status = 1;
	if (last_child > 0)
		waitpid(last_child, &status, 0);
	while (number_of_childs-- >= 0)
		wait(NULL);
	return (WEXITSTATUS(status));
}
