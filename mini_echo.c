/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:39:17 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/08 13:21:12 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

int	size_of_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	print_echo(char **argv, int i)
{
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] && argv[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
}

int	mini_echo(char **argv)
{
	int	i;
	int	n;
	int	t;

	i = 1;
	n = 0;
	t = 2;
	if (size_of_argv(argv) >= 1)
	{
		while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n' \
				&& (argv[i][t] == '\0' || argv[i][t] == 'n'))
		{
			while (argv[i][t] == 'n')
				t++;
			if (argv[i][t] != '\0')
				break ;
			n = 1;
			i++;
		}
		print_echo(argv, i);
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}
