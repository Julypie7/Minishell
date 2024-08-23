/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:54:22 by ineimatu          #+#    #+#             */
/*   Updated: 2024/08/23 11:11:26 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"

int	builtings(char **argv, t_info *info)
{
	if (argv[0] == "pwd")
		return (minipwd(info));
	else if (argv[0] == "cd")
		return (mini_cd(info));
	else if (argv[0] == "env")
		return (mini_env(info));
	else if (argv[0] == "export")
		return (mini_export(info));
	else if (argv[0] == "echo")
		return (mini_echo(argv));
	else if (argv[0] == "unset")
		return (mini_unset(info));
	else
		return (mini_exit(info));
}

int main(int argc, char **argv)
{
	builtings(argv
}
