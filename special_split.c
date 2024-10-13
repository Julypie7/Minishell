/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 00:03:36 by martalop          #+#    #+#             */
/*   Updated: 2024/10/14 00:37:18 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "struct.h"

void	skip_quote_content(const char *s, int *i)
{
	int	j;

	j = *i;
	if (s[j] == '\'')
	{
		j++;
		while (s[j] && s[j] != '\'')
			j++;
	}
	else if (s[j] == '\"')
	{
		j++;
		while (s[j] && s[j] != '\"')
			j++;
	}
	if (s[j])
		j++;
	*i = j;
}

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
			skip_quote_content(s, &i);
	}
	return (word);
}

int	split_simp_quote(char *s, int *i, char **array)
{
	i[0]++;
	i[1]++;
	while (s[i[0]] && s[i[0]] != '\'')
	{
		i[0]++;
		i[1]++;
	}
	if (s[i[0]] == '\'' && (!s[i[0] + 1] || s[i[0] + 1] == ' '))
	{
		i[0]++;
		i[1]++;
		array[i[2]] = ft_substr(s, (i[0] - i[1]), i[1]);
		if (!array[i[2]])
			return (2);
		i[1] = 0;
		i[2]++;
	}
	else if (s[i[0]] == '\'')
	{
		i[0]++;
		i[1]++;
	}
	return (0);
}

int	split_doubl_quote(char *s, int *i, char **array)
{
	i[0]++;
	i[1]++;
	while (s[i[0]] && s[i[0]] != '\"')
	{
		i[0]++;
		i[1]++;
	}
	if (s[i[0]] == '\"' && (!s[i[0] + 1] || s[i[0] + 1] == ' '))
	{
		i[0]++;
		i[1]++;
		array[i[2]] = ft_substr(s, (i[0] - i[1]), i[1]);
		if (!array[i[2]])
			return (2);
		i[1] = 0;
		i[2]++;
	}
	else if (s[i[0]] == '\"')
	{
		i[0]++;
		i[1]++;
	}
	return (0);
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
