/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:34:04 by martalop          #+#    #+#             */
/*   Updated: 2024/07/16 19:39:21 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"
#include "readline/history.h"

int	main()
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
