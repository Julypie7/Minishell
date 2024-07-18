/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:21:32 by martalop          #+#    #+#             */
/*   Updated: 2024/07/18 23:13:38 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (0);
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	**arr;
	int		found_at;
	int			i;
	int			j;

	i = 0;
	while (env[i])
	{
		j = 0;
		// variable name
		found_at = find_equal(env[i]);
		arr[j] = ft_substr(env[i], 0, found_at + 1);
		printf("%s\n", arr[j]);
		free(arr[j]);
		j++;
		// content of variable
		arr[j] = ft_substr(env[i], found_at + 1, ft_strlen(env[i]) - found_at);
		printf("%s\n", arr[j]);
		free(arr[j]);
		printf("\n");
		i++;
	}
	arr[j] = NULL;
}
