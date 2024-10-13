/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expanse2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 23:27:39 by martalop          #+#    #+#             */
/*   Updated: 2024/10/14 00:32:48 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "expansion.h"

char	*remove_all_quotes(char *str)
{
	char	**arr;
	char	*res;

	arr = NULL;
	res = NULL;
	arr = another_special_split(str);
	if (!arr)
		return (NULL);
	res = join_back_expanded(arr);
	free_array(arr);
	return (res);
}

void	final_quote_removal(char **final_arr, int i)
{
	char	**tmp_arr;
	char	*tmp_str;

	tmp_arr = NULL;
	tmp_str = NULL;
	if (find_simp_quote(final_arr[i]) + find_double_quote(final_arr[i]) > 1)
	{
		tmp_str = remove_all_quotes(final_arr[i]);
		free(final_arr[i]);
		final_arr[i] = tmp_str;
	}
	else if (ft_strchr(final_arr[i], '\'') || ft_strchr(final_arr[i], '\"'))
	{
		if (find_double_quote(final_arr[i]))
			tmp_arr = ft_split(final_arr[i], '\"');
		else if (find_simp_quote(final_arr[i]))
			tmp_arr = ft_split(final_arr[i], '\'');
		free(final_arr[i]);
		final_arr[i] = join_back_expanded(tmp_arr);
		free_array(tmp_arr);
	}
}

char	**join_all(char **arr)
{
	char	*final_str;
	char	**final_arr;
	int		i;

	i = 0;
	final_str = join_back_expanded(arr);
	if (!final_str)
		return (NULL);
	final_arr = my_special_split(final_str);
	if (!final_arr)
		return (free(final_str), NULL);
	free(final_str);
	while (final_arr && final_arr[i])
	{
		final_quote_removal(final_arr, i);
		i++;
	}
	return (final_arr);
}
// in join_back_expanded() I join parts with & without quotes
// in my_special_split() I separate by spaces ignoring the ones inside quotes

char	*fill_joined_str(char **divided_arr, int full_str_len)
{
	int		i;
	int		x;
	int		j;
	char	*res;

	i = 0;
	x = 0;
	res = malloc(sizeof(char) * (full_str_len + 1));
	if (!res)
		return (NULL);
	while (divided_arr && divided_arr[x])
	{
		j = 0;
		while (divided_arr[x][j])
		{
			res[i] = divided_arr[x][j];
			i++;
			j++;
		}
		x++;
	}
	res[i] = '\0';
	return (res);
}

char	*join_back_expanded(char **divided_arr)
{
	int		i;
	int		full_str_len;
	char	*res;

	i = 0;
	full_str_len = 0;
	while (divided_arr && divided_arr[i])
	{
		full_str_len += ft_strlen(divided_arr[i]);
		i++;
	}
	res = fill_joined_str(divided_arr, full_str_len);
	return (res);
}
