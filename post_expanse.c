/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expanse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:01:40 by martalop          #+#    #+#             */
/*   Updated: 2024/10/11 00:21:18 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "struct.h"
#include "expansion.h"

int	find_double_quote(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i])
				i++;
		}
		if (str[i] == '\"')
		{
			quote++;
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i])
				i++;
		}
		if (str[i])
			i++;
	}
	return (quote);
}

int	find_simp_quote(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str && str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			i++;
		}
		if (str[i] == '\'')
		{
			quote++;
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
		if (str[i])
			i++;
	}
	return (quote);
}

int		another_count_sections(char *s)
{
	int	i;
	int	sect;

	i = 0;
	sect = 0;
	while (s && s[i])
	{
		sect++;
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] == '\'')
				i++;
		}
		else if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
			if (s[i] == '\"')
				i++;
		}
		else
		{
			while (s[i] && s[i] != '\'' && s[i] != '\"') // al salir de aqui será o '\0' o comillas
				i++;
		}
	}
	return (sect);
}

char	**another_special_split(char *s)
{
	int	i;
	int	x;
	int	sect;
	int	word_start;
	int	ctr;
	char	**arr;

	i = 0;
	x = 0;
	ctr = 0;
	word_start = 0;
	sect = another_count_sections(s);
	arr = malloc(sizeof(char *) * (sect + 1));
	if (!arr)
		return (NULL);
	while (s && s[i])
	{
		word_start = 0;
		ctr = 0;
		if (s[i] == '\'')
		{
			i++;
			word_start = i;
			while (s[i] && s[i] != '\'')
			{
				i++;
				ctr++;
			}
			if (s[i] == '\'')
				i++;
		}
		else if (s[i] == '\"')
		{
			i++;
			word_start = i;
			while (s[i] && s[i] != '\"')
			{
				i++;
				ctr++;
			}
			if (s[i] == '\"')
				i++;
		}
		else
		{
			word_start = i;
			while (s[i] && s[i] != '\'' && s[i] != '\"')
			{
				i++;
				ctr++;
			}
		}
		arr[x] = ft_substr(s, word_start, ctr);
		if (!arr[x])
		{
			free_array(arr);
			return (NULL);
		}
		x++;
	}
	arr[x] = NULL;
	return (arr);
}

/*int	main(void)
{
//	char	**arr;
	int		i;
	char	*str;

	i = 0;
	str = " ajsg\"h''o'la\"\'akj\'";
	printf("_%s_\n", str);
	printf("simp quote num: %d\n", find_simp_quote(str));
	printf("double quote num: %d\n", find_double_quote(str));
//	arr = another_special_split(str);
//	while (arr[i])
//	{
//		printf("arr[%d]: _%s_\n", i, arr[i]);
//		i++;
//	}
//	if (!arr[i])
//		printf("%p\n", arr[i]);
}*/

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

char	**join_all(char **arr)
{
	char	*final_str;
	char	**final_arr;
	char	**tmp_arr;
	char	*tmp_str;
	int		i;

	i = 0;
	tmp_arr = NULL;
	tmp_str = NULL;
	final_str = join_back_expanded(arr); // junto partes con comillas, sin, con simples
	if (!final_str)
		return (NULL);
	final_arr = my_special_split(final_str); // separo en espacios ignorando los que estan dentro de comillas
	if (!final_arr)
		return (free(final_str), NULL);
	free(final_str);
	while (final_arr && final_arr[i])
	{
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
		i++;
	}
	return (final_arr);
}

char	*fill_joined_str(char **divided_arr, int full_str_len)
{
	int	i;
	int	x;
	int	j;
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
