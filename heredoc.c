/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:32:05 by martalop          #+#    #+#             */
/*   Updated: 2024/07/30 15:00:37 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include "execution.h"
#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

// --------- ./a.out      <<         limit   -----------
// --------- argv[0]    argv[1]     argv[2]  -----------

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
	while (str)
	{
		str = readline("> ");
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (1);
	//	printf("%d\n", fd);
		if (ft_strnstr(str, argv[2], ft_strlen(argv[2])))
		{
			free(str);
			close(fd);
			unlink(file_name);
			break ;
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		close(fd);
		free(str);
		i++;
	}

}
