/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expanse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:50:25 by martalop          #+#    #+#             */
/*   Updated: 2024/09/29 00:16:13 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include <stdio.h>

int		maxi_count(char *s)
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
			while (s[i] && s[i] != '\'' && s[i] != '\"')
				i++;
		}
	}
	return (sect);
}

int		count_sections(char *s)
{
	int	i;
	int	sect;

	i = 0;
	if (s)
		sect = 1;
	else
		return (0);
	while (s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && i != 0)
		{
			if (s[i] == '\"')
			{
				i++;
				while (s[i] != '\"')
					i++;
			}
			else if (s[i] == '\'')
			{
				i++;
				while (s[i] != '\'')
					i++;
			}
			sect++;
			printf("added new sect after comillas\n");
		}
		else if (s[i - 1] == '\"' || s[i -1] == '\'')
			sect++;
		i++;
	}
	return (sect);
}

/*int	main(void)
{
	char	*str;

	str = "$USER.hola\"$\'US\"ER\'$USjas ghdER\'\'\'";
	printf("input: %s\n", str);
	printf("res = %d\n", maxi_count(str));
	return (0);
}*/

char	**break_down_str(char *s)
{
	int	i;
	int	sect;
	int	*sect_len;
	char	**arr;

	i = 0;
	arr = NULL;
	
	// funcion que me cuenta las palabras/ segmentos analizables
	sect = count_sections(s);
	// funcion que me cuente cuanto mide cada segmento y me devuelva un split de cada uno de los segmento
	sect_len = section_length(s, sect_num);
	while (s && s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			if (i != 0)
				// guardar lo anterior en algun sitio
				// crear arr de 2 con el tamaño de i en arr[0]
			else
				// recorrer hasta el final de las comillas y crear arr con el tamaño de i en arr[0]
				// 
		}
	}
}

char	**full_expansion(char *str, t_envp *envp)
{
	char 	**arr;
	char	*str_expanded;
	int		i;
	
	i = 0;
	arr = break_down_str(str);
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		divide_str(arr[i]);// dividir en parte expandible y no expandible
		actual_expansion(char *, envp); // solo lo expandible de cada arr[i]
		join_back_expanded(); // juntar cada parte de cada arr[i]
		i++;
	}
	str_expanded = join_all_str();
	free(str);
	return (str_expanded);
}

int	expansion(t_cmd *cmd, t_envp *envp)
{
	t_cmd	*tmp_cmd;
	t_redir	*tmp_red;
	char	**aux;

	tmp_cmd = cmd;
	while (tmp_cmd)
	{
		tmp_red = tmp_cmd->redirs;
		//expando cmd->arr_cmd;
		while (tmp_cmd->arr_cmd && tmp_cmd->arr_cmd[i])
		{
			aux = full_expansion(tmp_cmd->arr_cmd[i], envp);
			// add aux to tmp_cmd->arr_cmd
			i++;
		}
		aux = NULL;
		//expando cmd->redirs->file_name;
		while (tmp_red)
		{
			aux = full_expansion(tmp_red->file_name, envp);
			handle_expanded_redir(aux, tmp_red); // si el char ** tiene más de un string, 'ambiguous redirect'
			tmp_red = tmp_red->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}
