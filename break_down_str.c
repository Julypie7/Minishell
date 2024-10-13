/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_down_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:44:18 by martalop          #+#    #+#             */
/*   Updated: 2024/10/13 03:45:39 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "struct.h"

static void	skip_quotes(int *i, char *s)
{
	int	j;

	j = *i;
	if (s[j] == '\'')
	{
		j++;
		while (s[j] && s[j] != '\'')
			j++;
		if (s[j] == '\'')
			j++;
	}
	else if (s[j] == '\"')
	{
		j++;
		while (s[j] && s[j] != '\"')
			j++;
		if (s[j] == '\"')
			j++;
	}
	*i = j;
}

int	count_sections(char *s)
{
	int	i;
	int	sect;

	i = 0;
	sect = 0;
	while (s && s[i])
	{
		sect++;
		if (s[i] == '\'' || s[i] == '\"')
			skip_quotes(&i, s);
		else
		{
			while (s[i] && s[i] != '\'' && s[i] != '\"')
				i++;
		}
	}
	return (sect);
}
// while (s[i] && s[i] != '\'' && s[i] != '\"') 
// al salir de ahi será o '\0' o comillas

void	handle_quotes_sect(int *i, int *ctr, char *s, char quote_type)
{
	int	j;
	int	c;

	j = *i;
	c = *ctr;
	if (s[j] == quote_type)
	{
		j++;
		c++;
		while (s[j] && s[j] != quote_type)
		{
			j++;
			c++;
		}
		if (s[j] == quote_type)
		{
			j++;
			c++;
		}
	}
	*i = j;
	*ctr = c;
}

void	handle_unquoted_sect(int *i, int *ctr, char *s)
{
	int	j;
	int	c;

	j = *i;
	c = *ctr;
	while (s[j] && s[j] != '\'' && s[j] != '\"')
	{
		j++;
		c++;
	}
	*i = j;
	*ctr = c;
}

char	**break_down_str(char *s)
{
	int		i[3];
	int		sect;
	char	**arr;

	ft_bzero(i, sizeof(int) * 3);
	sect = count_sections(s);
	arr = malloc(sizeof(char *) * (sect + 1));
	if (!arr)
		return (NULL);
	while (s && s[i[0]])
	{
		i[2] = 0;
		if (s[i[0]] == '\'' || s[i[0]] == '\"')
			handle_quotes_sect(&i[0], &i[2], s, s[i[0]]);
		else
			handle_unquoted_sect(&i[0], &i[2], s);
		arr[i[1]] = ft_substr(s, (i[0] - i[2]), i[2]);
		if (!arr[i[1]])
			return (free_array(arr), NULL);
		i[1]++;
	}
	arr[i[1]] = NULL;
	return (arr);
}
