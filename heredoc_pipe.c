/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:32:05 by martalop          #+#    #+#             */
/*   Updated: 2024/08/11 17:32:42 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include "execution.h"
#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

// --------- ./a.out      "<<"         limit   -----------
// --------- argv[0]    argv[1]     argv[2]  -----------

// PROBAR CON REDIRECCION DE SALIDA

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	char	*str;
	int		pipe_here[2];
	char	**arr;

	str = NULL;

	// creo pipe
	if (pipe(pipe_here) == -1)
		return (write(2, "pipe failed\n", 12), 1);
	while (1)
	{
		// leo de terminal
		str = readline("> ");		
	
		// si la linea leida de terminal es = a limiter, cierro el fd de escritura y paro el bucle de lectura
		if (!ft_strncmp(str, argv[2], ft_strlen(argv[2]) + 1))
		{
			free(str);
			close(pipe_here[1]);
			break ;
		}
		// si la linea leida NO es = limiter, guardo la linea en el fd de escritura de la pipe
		write(pipe_here[1], str, ft_strlen(str));
		write(pipe_here[1], "\n", 1);

		free(str);
	}
	/* REDIR Y EJECUCION CON COMANDO
	if (dup2(pipe_here[0], 0) == -1) // la parte de lectura de la pipe ya tiene escrito el contenido del heredoc
		return (write(2, "dup2 failed\n", 12), 1);
	arr = malloc(sizeof(char *) * 2);
	arr[0] = "cat";
	arr[1] = NULL;
	if (execve("/usr/bin/cat", arr, env) == -1)
		return (write(2, "execve failed\n", 14), 1);
	*/
}
