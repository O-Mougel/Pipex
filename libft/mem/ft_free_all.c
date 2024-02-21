/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:42:04 by omougel           #+#    #+#             */
/*   Updated: 2024/02/21 14:45:21 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_free_all(const char *str, ...)
{
	va_list	var;
	size_t	i;

	i = 0;
	if (!str)
		return ;
	va_start(var, str);
	while (str[i])
	{
		if (str[i] == 's')
			free(va_arg(var, char *));
		if (str[i] == 'a')
			ft_free_arr(va_arg(var, char **));
		if (str[i] == 'l')
			ft_lstclear(va_arg(var, t_list **), ft_free_arr);
		i++;
	}
	va_end(var);
}
