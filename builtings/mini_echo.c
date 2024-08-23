/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:21:52 by ineimatu          #+#    #+#             */
/*   Updated: 2024/08/23 12:26:48 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "minishell.h"
#include "struct.h"
#include <unistd.h>
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
// Example implementation of ft_strcmp
int ft_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

// Example implementation of fr_putstr_fd (similar to puts)
void fr_putstr_fd(const char *s, int fd) {
    write(fd, s, strlen(s));
}*/

int size_of_argv(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}


void mini_echo(char **argv)
{
	int i;
	int n;

	i = 1;
	n = 0;
	if (size_of_argv(argv) >= 1)
	{
		while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
		{
			n = 1;
			i++;
		}
		while (argv[i])
		{
			fr_putstr_fd(argv[i], 1);
			if (argv[i + 1] && argv[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n == 0)
		write(1, "\n", 1);
}
/*
int main(int argc, char **argv)
{
	mini_echo(argv);
	return (0);
}*/
