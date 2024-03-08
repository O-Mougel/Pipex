/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:05:09 by omougel           #+#    #+#             */
/*   Updated: 2024/03/07 16:58:21 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

char	**find_command(char *str, char **envp);
void	pipex(int *fd_in, char **argv, char **envp, char *str);
int		last_child(int fd_in, char **argv, char **envp, int argc);
int		wait_all_child(int last_child, int number_of_childs);

#endif // !PIPEX_H
