/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:32:05 by martalop          #+#    #+#             */
/*   Updated: 2024/08/10 22:04:56 by martalop         ###   ########.fr       */
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
// PROOBAR CON PIPE TMB

int	main(int argc, char **argv)
{
	(void) argc;
	char	*str;
	int		fd;
	int		i;
	char	*file_name;

	i = 0;
	str = NULL;
	file_name = "tmp_file";

	// creo archivo
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
	// es trunc prq no me deberia hacer append cuando el archivo ya esta creado y vuelvo a hacer un heredoc
	if (fd == -1)
		return (1);

	while (1)
	{
		// leo de terminal
		str = readline("> ");		
	
		// si la linea leida de terminal es = a limiter, cierro el archivo y paro el bucle de lectura
		if (!ft_strncmp(str, argv[2], ft_strlen(argv[2]) + 1))
		{
			free(str);
			close(fd);
			unlink(file_name);
			break ;
		}
		// si la linea leida NO es = limiter, guardo la linea en el fd del archivo creado
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);

		free(str);
		i++;
	}
}
