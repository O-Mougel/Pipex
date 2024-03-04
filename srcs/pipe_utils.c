/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:16:32 by omougel           #+#    #+#             */
/*   Updated: 2024/03/04 10:18:11 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_close_all(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	ft_exit(void)
{
	perror(NULL);
	exit(errno);
}
