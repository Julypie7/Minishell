/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:55:54 by ineimatu          #+#    #+#             */
/*   Updated: 2024/08/23 12:56:17 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_envp
{
	char 	*key;
	char	*value;
	struct s_envp 	*next;
} t_envp;

typedef	struct s_info
{
	t_envp	*envp;
} t_info;

