/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:08:52 by omougel           #+#    #+#             */
/*   Updated: 2024/01/29 16:46:03 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int	i;
	//char str[10];

	i = open("file3", O_RDONLY);
	printf("%d\n", i);
	printf("%s\n", strerror(errno));
	perror(NULL);
	write(i, "hello", 5);
	printf("%s\n", strerror(errno));
	perror(NULL);
	printf("1");
	return (0);
}
