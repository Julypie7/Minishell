/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_julia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:56:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/18 16:22:42 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	int		i;

	i = 0;
	if (argc != 1)
	{
		printf("This program does not accept arguments\n");
		exit(1);
	}
	while (i < 5)
	{
		str = readline("our minishell > ");
		printf("user input: %s\n", str);
		//clasificar str
		free(str);
		i++;
	}
	rl_clear_history();
	return (0);
}
