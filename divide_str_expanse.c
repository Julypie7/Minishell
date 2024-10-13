/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expanse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:50:25 by martalop          #+#    #+#             */
/*   Updated: 2024/10/13 04:33:43 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "execution.h"
#include "expansion.h"
#include <stdio.h>

int	count_divisions(char *str)
{
	int	i;
	int	div;

	i = 0;
	div = 0;
	if (!ft_strchr(str, '$'))
		return (1);
	while (str && str[i])
	{
		if (str[i] && str[i] != '$')
		{
			div++;
			while (str[i] != '$' && str[i])
				i++;
		}
		if (str[i] && str[i++] == '$')
		{
			div++;
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
		}
	}
	return (div);
}

int	find_quote_type(char *str)
{
	if (str[0] == '\'')
		return (1);
	else if (str[0] == '\"')
		return (2);
	else
		return (0);
}

int	handle_non_var_div(char *str, int *i, char **div_arr)
{
	int	j;

	j = i[0];
	i[2] = 0;
	if (str[j] && str[j] != '$')
	{
		while (str[j] != '$' && str[j])
		{
			j++;
			i[2]++;
		}
		div_arr[i[1]] = ft_substr(str, j - i[2], i[2]);
		if (!div_arr[i[1]])
			return (free_array(div_arr), 2);
		i[1]++;
	}
	i[0] = j;
	return (0);
}

int	handle_var_div(char *str, int *i, char **div_arr)
{
	if (str[i[0]] && str[i[0]++] == '$')
	{
		i[2]++;
		if (str[i[0]] != '?')
		{
			while (ft_isalnum(str[i[0]]) || str[i[0]] == '_')
			{
				i[0]++;
				i[2]++;
			}
		}
		else
		{
			i[0]++;
			i[2]++;
		}
		div_arr[i[1]] = ft_substr(str, i[0] - i[2], i[2]);
		if (!div_arr[i[1]])
			return (free_array(div_arr), 2);
		i[1]++;
	}
	return (0);
}

char	**divide_str(char *str)
{
	int		i[3];
	int		divs;
	int		ctr;
	char	**div_arr;

	ft_bzero(i, sizeof(int) * 3);
	divs = count_divisions(str);
	div_arr = malloc(sizeof(char *) * (divs + 1));
	if (!div_arr)
		return (NULL);
	while (str && str[i[0]])
	{
		if (handle_non_var_div(str, i, div_arr) == 2)
			return (NULL);
		i[2] = 0;
		if (handle_var_div(str, i, div_arr) == 2)
			return (NULL);
	}
	div_arr[i[1]] = NULL;
	return (div_arr);
}

/*int	main(void)
{
	char	*str;
	char	**arr;
	int		i;

	i = 0;
	str = "\"$hola chao\"";
	arr = NULL;
	printf("input: %s\n", str);
	printf("res = %d\n", count_divisions(str));
	arr = divide_str(str);
	if (!arr)
		printf("malloc err\n");
	while (arr && arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
	if (!arr[i])
		printf("%s\n", arr[i]);
//	free_array(arr);
	return (0);
}*/
