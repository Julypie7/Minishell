/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:56:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/24 13:15:28 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "lexer.h"

void	init_struct(t_info *info, char **env)
{
	char	**arr;

	info->rl = NULL;
	info->ex_stat = 0;
	info->envp = NULL;
	info->tokens = NULL;
	env_to_list(info, env);
//	print_env(info->envp);
	arr = envlst_to_arr(info->envp);
//	print_char_arr(arr);
	free_array(arr);
}

void	start_reading(t_info *info)
{
	int i;

	i = 0;
	while (i < 5)
	{
		info->rl = readline("our minishell > ");
		/*printf("user input: %s\n", info->rl);*/
		valid_line(info);
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
	free_envlst(info.envp);
	return (info.ex_stat);
}
