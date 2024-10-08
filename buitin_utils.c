/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:03:29 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/08 13:05:12 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*ft_getenv(char *str, t_envp *lst)
{
	t_envp	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return (tmp->value);
		else
			tmp = tmp->next;
	}
	return ("path doesn't exist\n");
}

long long	ft_atoi_ex(char *str)
{
	long long	nbr;
	long long	i;
	int			flag;

	nbr = 0;
	i = 0;
	flag = 0;
	while (str[i] == '0')
		i++;
	if (str[i] == '-')
		flag = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = (str[i] - '0') + nbr * 10;
		i++;
	}
	if (flag == -1)
		nbr = nbr * flag;
	return (nbr);
}

int	check_zero_case(char *str, t_info *info, t_cmd *cmds, t_exec *exec_info)
{
	int	i;

	i = 0;
	if (!str[i])
		ft_exit(info, 0, cmds, exec_info);
	if (str[i] == '-' && str[i + 1] == '0')
		i++;
	if (str[i] == '-' && str[i + 1] != '0')
		return (0);
	while (str && str[i] == '0')
		i++;
	if (!str[i])
		return (i - 1);
	else
		return (i);
}
