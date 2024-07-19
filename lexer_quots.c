/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:31:23 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/19 14:41:42 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
# include "readline/readline.h"
# include "readline/history.h"

static size_t	ft_strlen(char *s)
{
	size_t	e;

	e = 0;
	while (s[e] != '\0')
		e++;
	return (e);
}


void	exit_free(char *str, int i)
{
	write(1, str, ft_strlen(str));
	if (i == 1)
	{
		exit(1);
		//free(env);
	}
}

void valid_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while(line[i] != '"' && line[i] != '\0')
				i++;
			if(line[i] == '\0')
				return(exit_free("Doble quotes are not closed\n", 1));
		}
		if (line[i] == 39)
		{
			i++;
			while (line[i] != 39 && line[i] != '\0')
				i++;
			if(line[i] == '\0')
				return(exit_free("Single quotes aren't closed\n", 1));
		}
		if(line[i])
			i++;
		if (line[i] =='\0')
			return ;
	}
}

int main()
{
	char *str;
	
	while (1)
	{
		str = readline("Prompt >");
		valid_line(str);
		free(str);
	}
	rl_clear_history();
	return (0);
}


