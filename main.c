/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:56:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/22 14:58:53 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	init_struct(t_info *info, char **env)
{
	info->rl = NULL;
	info->ex_stat = 0;
	info->envp = NULL;
	env_to_list(info, env);
//	print_env(&info->envp);
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
	return (info.ex_stat);
}
