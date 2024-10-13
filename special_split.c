/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 00:03:36 by martalop          #+#    #+#             */
/*   Updated: 2024/10/11 00:04:34 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "struct.h"

static int	word_counter(const char *s)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		if (s[i])
			word++;
		while (s[i] && s[i] != ' ')
		{
			if (s[i] == '\'')
			{
				i++;
				while (s[i] && s[i] != '\'')
					i++;
			}
			else if (s[i] == '\"')
			{
				i++;
				while (s[i] && s[i] != '\"')
					i++;
			}
			if (s[i])
				i++;
		}
	}
	return (word);
}

char	**fill_words(char *s, char **array)
{
	int		i;
	int		word;
	int		ctr;
	int		x;

	word = 0;
	ctr = 0;
	x = 0;
	i = 0;
	while (s && s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i])
			word++;
		while (s[i] && s[i] != ' ')
		{
			if (s[i] == '\'')
			{
				i++;
				ctr++;
				while (s[i] && s[i] != '\'')
				{
					i++;
					ctr++;
				}
				if (s[i] == '\'' && (!s[i + 1] || s[i + 1] == ' '))
				{
					i++;
					ctr++;
					array[x] = ft_substr(s, (i - ctr), ctr);
					if (!array[x])
						return (NULL);
					ctr = 0;
					x++;
				}
				else if (s[i] == '\'')
				{
					i++;
					ctr++;
				}
			}
			else if (s[i] == '\"')
			{
				i++;
				ctr++;
				while (s[i] && s[i] != '\"')
				{
					i++;
					ctr++;
				}
				if (s[i] == '\"' && (!s[i + 1] || s[i + 1] == ' '))
				{
					i++;
					ctr++;
					array[x] = ft_substr(s, (i - ctr), ctr);
					if (!array[x])
						return (NULL);
					ctr = 0;
					x++;
				}
				else if (s[i] == '\"')
				{
					i++;
					ctr++;
				}
			}
			else if (s[i])
			{
				i++;
				ctr++;
			}
		}
		if ((s[i] == ' ' || (!s[i] && s[i - 1] != '\'' && s[i -1] != '\"')) && word && ctr > 0)
		{
			array[x] = ft_substr(s, i - ctr, ctr);
			if (!array[x])
				return (NULL);
			ctr = 0;
			x++;
		}
	}
	array[x] = NULL;
	return (array);
}

char	**my_special_split(char *s)
{
	int		i;
	int		wordcount;
	char	**array;

	i = 0;
	wordcount = word_counter(s);
	array = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!array)
		return (NULL);
	if (!fill_words(s, array))
		return (free_array(array), NULL);
	return (array);
}
