/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:14:55 by omougel           #+#    #+#             */
/*   Updated: 2024/02/22 17:27:47 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

t_list	*fill_pipex(char **argv, char **envp);
void	ft_do_the_pipe(char **argv, t_list *pipex, char **envp);

#endif // !PIPEX_H
