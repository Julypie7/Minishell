/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:41:51 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/14 14:08:09 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

void	ft_exit(t_info *info, int ex_stat, t_cmd *cmds, t_exec *exec_info)
{
	if (exec_info->cmd_num == 1 && !cmds->next)
		printf("exit\n");
	free_child(info, cmds, exec_info);
	if (info->copy)
		free_envlst(info->copy);
	exit(ex_stat);
}

void	exit_error(t_info *info, int ex_st, t_cmd *cmds, t_exec *exec_info)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd("numeric argument required\n", 2);
	ft_exit(info, ex_st, cmds, exec_info);
}

void	check_arg(char *arg, t_info *info, t_cmd *cmds, t_exec *exec_info)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (ft_strlen(&(arg[i])) > 19)
		exit_error(info, 2, cmds, exec_info);
	if (arg[0] == '-')
	{
		if (ft_strncmp("9223372036854775808", &(arg[i]), \
					ft_strlen(&(arg[i]))) < 0)
			exit_error(info, 2, cmds, exec_info);
	}
	else
	{
		if (ft_strncmp("9223372036854775807", &(arg[i]), \
					ft_strlen(&(arg[i]))) < 0)
			exit_error(info, 2, cmds, exec_info);
	}
}

int	check_long(char *arg, t_info *info, t_cmd *cmds, t_exec *exec_info)
{
	int	i;

	i = 0;
	if (!arg)
		ft_exit(info, 0, cmds, exec_info);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if ((arg[i] != '\f') && (arg[i] != '\t') && (arg[i] != '\r') \
				&& (arg[i] != '\v') && (arg[i] != ' '))
		{
			if (arg[i] < 48 || arg[i] > 57)
				exit_error(info, 1, cmds, exec_info);
		}
		i++;
	}
	return (1);
}

int	mini_exit(char **av, t_info *info, t_cmd *cmds, t_exec *exec_info)
{
	int			i;
	long long	ex_stat;

	i = 0;
	while (av && av[i])
		i++;
	if (i >= 3)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else
	{
		if (check_long(av[1], info, cmds, exec_info) && av[1])
		{
			i = check_zero_case(av[1], info, cmds, exec_info);
			check_arg(av[1] + i, info, cmds, exec_info);
			ex_stat = ft_atoi_ex(av[1] + i);
			if (ex_stat > 255 || ex_stat < 0)
				ex_stat = ex_stat % 256;
			ft_exit(info, ex_stat, cmds, exec_info);
		}
	}
	return (0);
}
