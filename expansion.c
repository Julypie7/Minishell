/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:58:48 by martalop          #+#    #+#             */
/*   Updated: 2024/10/13 04:32:08 by martalop         ###   ########.fr       */
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
		return (ft_itoa(prev_ex_stat)); //deberia protegerla
	return (NULL);
}

char	*actual_expansion(char *str, t_envp *envp, int quote_type, int prev_ex_stat)
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
	res = ft_strdup(str); // no existe la variable o no tengo que expandir(prq venia de comillas simples), asi que devuelvo lo mismo que me ha llegado
	return (res);
}

char	**full_expansion(char *str, t_envp *envp, int prev_ex_stat)
{
	char 	**arr;
	char 	**divided_arr;
	char 	**final_arr;
	char 	*tmp_expanded;
	char 	*tmp_str;
	int		i;
	int		j;
	int		quote_type;
	int		x;
	
	i = 0;
	j = 0;
	quote_type = 0;
	tmp_str = NULL;
	final_arr = NULL;
	tmp_expanded = NULL;
	arr = break_down_str(str); // en sin comillas, con dobles o con simples
	if (!arr)
		return (NULL);
	while (arr && arr[i])
	{
		x = 0;
		quote_type = find_quote_type(arr[i]);
		divided_arr = divide_str(arr[i]); // en partes expandibles y no expandibles
		while (x < find_arr_size(divided_arr) && divided_arr && divided_arr[x])
		{
			if (ft_strchr(divided_arr[x], '$'))
			{
				tmp_expanded = actual_expansion(divided_arr[x], envp, quote_type, prev_ex_stat);
				if (!tmp_expanded)
					return (write(2, "malloc error\n", 13), NULL);
			}
			else
				tmp_expanded = ft_strdup(divided_arr[x]);
			free(divided_arr[x]);
			divided_arr[x] = tmp_expanded;
			x++;
		}
		tmp_str = join_back_expanded(divided_arr); // de div_arr (segmentos expandibles y no expandibles)
		free_array(divided_arr);
		free(arr[i]);
		if (!tmp_str)
			return (NULL);
		arr[i] = tmp_str;
		i++;
	}
	final_arr = join_all(arr); // de arr (comillas simpl/dobl y sin)
	if (!final_arr)
		return (NULL);
	free_array(arr);
	return (final_arr);
}

void	handle_expanded_redir(char **aux, t_redir *tmp_red)
{
	if (!aux[0] || aux[1])
		tmp_red->amb_red = 1;
	else
	{
		free(tmp_red->file_name);
		tmp_red->file_name = ft_strdup(aux[0]);
	}
	free_array(aux);
}
int	expand_files(t_redir *redirs, t_envp *envp, int prev_ex_stat)
{
	t_redir	*tmp_red;
	char	**aux;
	int		i;

	i = 0;
	tmp_red = redirs;
	while (tmp_red)
	{
//		tmp_red->file_name = ft_strdup("\"$test'\"hol\"$bla\"");
//		printf("\ntmp_red->file_name: %s\n", tmp_red->file_name);
		aux = NULL;
		aux = full_expansion(tmp_red->file_name, envp, prev_ex_stat);
		if (!aux)
		{
			printf("expansion returns NULL\n");
			return (1);
		}
		handle_expanded_redir(aux, tmp_red); 
		tmp_red = tmp_red->next;
	}
	return (0);
}

char	**cmd_expansion(char **arr_cmd, t_envp *envp, int prev_ex_stat, int *malloc_flag)
{
	int		i;
	int		x;
	char	**aux;
	char	**new_cmd;

	x = 0;
	aux = NULL;
	new_cmd = NULL;
	while (arr_cmd && arr_cmd[x])
	{
		i = 0;
	//	if (x == 1)
	//	arr_cmd[x] = ft_strdup("\"akj\"shdkj\"aj'$shd\"la\'k \"\'js");
	//	printf("arr_cmd[%d] before expansion: %s\n", x, arr_cmd[x]);
		aux = full_expansion(arr_cmd[x], envp, prev_ex_stat);
		if (!aux)
		{
			*malloc_flag += 1;
			return (NULL);
		}
		while (aux && aux[i])
		{
			new_cmd = add_to_array(aux[i], new_cmd);
			if (!new_cmd)
			{
				*malloc_flag += 1;
				return (NULL);
			}
			i++;
		}
		free_array(aux);
		x++;
	}
	free_array(arr_cmd);
	return (new_cmd);
}
