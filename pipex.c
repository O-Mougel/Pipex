/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:13:01 by omougel           #+#    #+#             */
/*   Updated: 2024/02/14 18:36:52 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int i;

	i = 0;
	if (argc == 0 || argv == NULL)
		return (0);
	while (envp[i])
		ft_printf("%s\n",envp[i++]);
	return (0);
}
