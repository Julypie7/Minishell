/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:30:32 by martalop          #+#    #+#             */
/*   Updated: 2024/09/18 15:09:51 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "execution.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int	heredoc(char *lim)
{
	char	*str;
	int		pipe_here[2];

	str = NULL;
	if (pipe(pipe_here) == -1)
		return (write(2, "pipe failed\n", 12), -1);
	while (1)
	{
		str = readline("> ");
		if (!ft_strncmp(str, lim, ft_strlen(lim) + 1))
		{
			free(str);
			close(pipe_here[1]);
			break ;
		}
		write(pipe_here[1], str, ft_strlen(str));
		write(pipe_here[1], "\n", 1);
		free(str);
	}
	return (pipe_here[0]);
}
