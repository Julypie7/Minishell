/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:56:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/19 11:31:48 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

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

void	env_to_list(t_info *info, char **env)
{
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
		info->
		j++;
		// content of variable
		arr[j] = ft_substr(env[i], found_at + 1, ft_strlen(env[i]) - found_at);
		printf("%s\n", arr[j]);
		printf("\n");
		i++;
	}
	arr[j] = NULL;

}

void	init_struct(t_info *info, char **env)
{
	(void) env;
	info->rl = NULL;
	info->ex_stat = ft_strlen("hola");
	env_to_list(info, env);
}

void	start_reading(t_info *info)
{
	int i;

	i = 0;
	while (i < 5)
	{
		info->rl = readline("our minishell > ");
		printf("user input: %s\n", info->rl);
		//clasificar string
		free(info->rl);
		i++;
	}
	rl_clear_history();

}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	t_info	info;

	if (argc != 1)
	{
		printf("This program does not accept arguments\n");
		exit(1);
	}
	init_struct(&info, env);
	start_reading(&info);
	return (0);
}
