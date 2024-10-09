/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:09:11 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/09 12:36:58 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

int	how_much(char **argv, t_info *info)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i < 2)
	{
		if (!info->copy)
			copy_env(info, info->envp);
		print_env_sorted(info);
		return (0);
	}
	return (1);
}

int	check_of_arg(char **argv, int len, t_info *info)
{
	while (argv[len])
	{
		/*if (argv[len][0] == '\0')
			return (len - 1); //becuase of null arg which id coming from lexer;*/
		if (parse_export(argv[len]) == 0)
		{
			printf("bash: export: `%s': not a valid identifier\n", argv[len]);
			return (-1);
		}
		len++;
	}
	return (len);
}

int	parse_export(char *str)
{
	int	i;
	int	equal;

	i = 0;
	equal = find_equal(str);
	if (ft_isdigit(str[0]))
		return (0);
	if (str[0] == '=')
		return (0);
	if (str[0] == '"' && str[1] == '"')
		return (0);
	if (str[0] == '\'' && str[1] == '\'')
		return (0);
	if (plus_sign(str, equal) == 0)
		return (0);
	while (str[i] && i != equal)
	{
		if (check_special_characters(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_special_characters(char c)
{
	if (c == '@' || c == '%' || c == '^' || c == '*' || \
			c == '-')
		return (0);
	return (1);
}

int	plus_sign(char *str, int equal)
{
	int	i;

	i = 1;
	while (str[i] && i != equal)
	{
		if (str[0] == '+')
			return (0);
		if (str[i] == '+' && str[i - 1] == '=')
			return (1);
		if (str[i] == '+')
			return (0);
		i++;
	}
	return (1);
}
