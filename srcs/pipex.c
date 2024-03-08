/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:09:00 by omougel           #+#    #+#             */
/*   Updated: 2024/03/08 14:54:25 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	fd_in;
	int	pid;
	int	status;

	i = 0;
	if (argc != 5)
		return (ft_putstr_fd("Invalid number of arguments", 2), 1);
	if (!envp || !*envp)
		return (ft_putstr_fd("No environement set", 2), 1);
	pipex(&fd_in, argv, envp, argv[i + 2]);
	pid = last_child(fd_in, argv, envp, argc);
	status = wait_all_child(pid, i);
	return (status);
}
