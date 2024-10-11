/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:33:38 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/11 14:09:44 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_norm_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		// should be globar assign ex_stat to 130;
	}
}

void	handle_hd_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		exit (130);
	}
}

void	sig_def(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_handl(int signal)
{
	if (WIFEXITED(status)) //returns true if child erminted normally with exit;
		global = WEEXITSTATUS(status); //return exit status of child;
	else if (WIFSIGNALED(status)) //returns nn-zero if child terminated bc it recieve signal that hasnt been handled
	{
		if (WTERMSIG(status) = SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			global = 131;
		}
		else if (WTERSIG(status) = SIGINT)
		{
			ft_putstr_fd("\n", 2);
			global = 130;
		}
	}
}

void	wif_herdoc(int signal)
{
	if (WIFEXITED(status))
	{
		if (status == 256)
		{
			global = 1;
			info->ex_stat = 1;
		}
	}
	else if (WIFSIGNALED(status) && WTERSIG(status) = SIGINT)
	{
		global = 130;
		info->ex_stat = 1;
	}
}
