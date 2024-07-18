/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:34:04 by martalop          #+#    #+#             */
/*   Updated: 2024/07/18 12:55:17 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **env)
{
	char	*str;
	int		i;

	i = 0;
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
