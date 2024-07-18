/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:56:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/18 23:35:25 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

/*void	env_to_list(t_info *info, char **env)
{
	char	*key;
	char	*value;

	// splt de '=' de env[i] hasta que ahi haya un NULL?
}*/

void	init_struct(t_info *info, char **env)
{
	(void) env;
	info->rl = NULL;
	info->ex_stat = ft_strlen("hola");
//	env_to_list(info, env);
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
