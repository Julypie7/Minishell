/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:55:31 by martalop          #+#    #+#             */
/*   Updated: 2024/10/10 15:16:59 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "execution.h"

int	find_heredocs(t_cmd *cmds)
{
	t_cmd	*tmp_cmd;
	t_redir	*tmp_rdir;

	tmp_cmd = cmds;
	while (tmp_cmd)
	{
		if (tmp_cmd->redirs)
		{
			tmp_rdir = tmp_cmd->redirs;
			while (tmp_rdir)
			{
				if (tmp_rdir->type == HEREDOC)
					tmp_rdir->fd = heredoc(tmp_rdir->file_name);
				tmp_rdir = tmp_rdir->next;
			}
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}

int	open_redir(t_cmd *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->amb_red == 1)
		{
			write(2, tmp->file_name, ft_strlen(tmp->file_name));
			write(2, ": ambiguous redirect\n", 21);
			return (1);
		}
		if (tmp->type == INPUT || tmp->type == HEREDOC)
		{
			if (open_input(tmp, cmd) == 1)
				return (1);
		}
		else if (tmp->type == OUTPUT || tmp->type == APPEND)
		{
			if (open_output(tmp, cmd) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redirect(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, 0) == -1)
		{
			write(2, "dup2 in failed\n", 15);
			return (1);
		}
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, 1) == -1)
		{
			write(2, "dup2 out failed\n", 16);
			return (1);
		}
		if (cmd->fd_out != -1)
			close(cmd->fd_out);
	}
	return (0);
}

int	open_input(t_redir *tmp, t_cmd *cmd)
{
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (tmp->type == INPUT)
	{
		cmd->fd_in = open(tmp->file_name, O_RDONLY);
		if (cmd->fd_in == -1)
		{
			if (tmp->file_name && !tmp->file_name[0])
				write(2, " : ", 3);
			perror(tmp->file_name);
			return (1);
		}
	}
	else if (tmp->type == HEREDOC)
	{
		cmd->fd_in = tmp->fd;
		tmp->fd = -1;
		if (cmd->fd_in == -1)
		{
			perror(tmp->file_name);
			return (1);
		}
	}
	return (0);
}

int	open_output(t_redir *tmp, t_cmd *cmd)
{
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	if (tmp->type == OUTPUT)
	{
		cmd->fd_out = open(tmp->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
		{
			perror(tmp->file_name);
			return (1);
		}
	}
	else if (tmp->type == APPEND)
	{
		cmd->fd_out = open(tmp->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cmd->fd_out == -1)
		{
			perror(tmp->file_name);
			return (1);
		}
	}
	return (0);
}
