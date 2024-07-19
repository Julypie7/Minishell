/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:56:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/19 14:49:01 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	find_arr_len();

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
	int		found_at;
	int			i;
	int			j;
	t_envp		*tmp;
	t_envp		*node;

	i = 0;
//	i = find_arr_len(env);

	//tengo que hacer malloc para cada nodo, para cada t_envp
	//
	node = malloc(sizeof(t_envp) * 1);
	if (!arr)
	{
		write(2, "malloc error at env copy creation\n", 34);
		exit(1);
	}
	tmp = info->envp;
	while (env[i])
	{
		j = 0;
		// variable name
		found_at = find_equal(env[i]);
		tmp->key = ft_substr(env[i], 0, found_at + 1);

		printf("%s\n", tmp->key);
		j++;
		// content of variable
		tmp->value = ft_substr(env[i], found_at + 1, ft_strlen(env[i]) - found_at);
		printf("%s\n", tmp->value); 
		printf("\n");
		tmp = tmp->next;
		i++;
	}
	arr[j] = NULL;

}

void	init_struct(t_info *info, char **env)
{
	(void) env;
	info->rl = NULL;
	info->ex_stat = 0;
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
