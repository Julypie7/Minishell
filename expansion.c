/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:58:48 by martalop          #+#    #+#             */
/*   Updated: 2024/10/13 14:38:53 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "expansion.h"
#include "libft/libft.h"

char	*search_in_envp(char *str, t_envp *envp, int prev_ex_stat)
{
	char	*new_value;
	char	*aux_key;

	while (envp)
	{
		aux_key = ft_substr(envp->key, 0, (ft_strlen(envp->key) - 1));
		if (!ft_strcmp(str, aux_key))
		{
			new_value = ft_strdup(envp->value);
			free(aux_key);
			aux_key = NULL;
			return (new_value);
		}
		free(aux_key);
		aux_key = NULL;
		envp = envp->next;
	}
	if (str[0] == '?' && !str[1])
		return (ft_itoa(prev_ex_stat));
	return (NULL);
}

char	*actual_expansion(char *str, t_envp *envp, \
		int quote_type, int prev_ex_stat)
{
	char	*new_value;
	char	*res;

	res = NULL;
	new_value = NULL;
	if (!quote_type || quote_type == 2)
	{
		if (str[0] == '$' && !str[1])
			return (ft_strdup("$"));
		new_value = search_in_envp(str + 1, envp, prev_ex_stat);
		if (!new_value)
		{
			res = ft_strdup("");
			return (res);
		}
		return (new_value);
	}
	res = ft_strdup(str);
	return (res);
}

char	*expand_divided_arr(char *divided_str, t_envp *envp, \
		int quote_type, int prev_ex_stat)
{
	char	*tmp_expanded;

	tmp_expanded = NULL;
	if (ft_strchr(divided_str, '$'))
	{
		tmp_expanded = actual_expansion(divided_str, envp, \
				quote_type, prev_ex_stat);
		if (!tmp_expanded)
			return (write(2, "malloc error\n", 13), NULL);
	}
	else
	{
		tmp_expanded = ft_strdup(divided_str);
		if (!tmp_expanded)
			return (write(2, "malloc error\n", 13), NULL);
	}
	free(divided_str);
	return (tmp_expanded);
}

char	*handle_sect_to_expand(char *str, t_envp *envp, int prev_ex_stat)
{
	int		x;
	int		quote_type;
	char	**divided_arr;
	char	*tmp_str;

	x = 0;
	tmp_str = NULL;
	divided_arr = NULL;
	quote_type = find_quote_type(str);
	divided_arr = divide_str(str);
	while (x < find_arr_size(divided_arr) && divided_arr && divided_arr[x])
	{
		divided_arr[x] = expand_divided_arr(divided_arr[x], envp, \
				quote_type, prev_ex_stat);
		if (!divided_arr[x])
			return (free_array(divided_arr), NULL);
		x++;
	}
	tmp_str = join_back_expanded(divided_arr);
	free_array(divided_arr);
	free(str);
	return (tmp_str);
}

// divided_arr = DIVIDE_STR() splits into expandible 
// & not expandible divisions (vars and any other characters)
// ! We handle quotes as any other characters !

// JOIN_BACK_EXPANDED joins the division of divided_arr 

char	**full_expansion(char *str, t_envp *envp, int prev_ex_stat)
{
	char	**arr;
	char	**final_arr;
	int		i;

	i = 0;
	final_arr = NULL;
	arr = break_down_str(str);
	if (!arr)
		return (NULL);
	while (arr && arr[i])
	{
		arr[i] = handle_sect_to_expand(arr[i], envp, prev_ex_stat);
		if (!arr[i])
			return (free_array(arr), NULL);
		i++;
	}
	final_arr = join_all(arr);
	free_array(arr);
	return (final_arr);
}

// BREAK_DOWN_STR() splits into "". '' and no quotes sections WITH the "" & ''
// JOIN_ALL() of arr of the broken down sections
