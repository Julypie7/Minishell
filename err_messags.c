/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_messags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:18:25 by martalop          #+#    #+#             */
/*   Updated: 2024/09/03 15:36:23 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "struct.h"
#include "libft/libft.h"

void	cmd_not_found(char *str)
{
	write(2, "Command not found: ", 19);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}
