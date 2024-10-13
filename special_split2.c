/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:00:06 by martalop          #+#    #+#             */
/*   Updated: 2024/10/13 20:02:03 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "struct.h"

int	handle_all(char *s, int *i, char **array)
{
	if (s[i[0]] == '\'')
	{
		if (split_simp_quote(s, i, array) == 2)
			return (2);
	}
	else if (s[i[0]] == '\"')
	{
		if (split_doubl_quote(s, i, array) == 2)
			return (2);
	}
	else if (s[i[0]])
	{
		i[0]++;
		i[1]++;
	}
	return (0);
}

int	handle_new_word(char *s, int *i, char **array, int word)
{
	if ((s[i[0]] == ' ' || (!s[i[0]] && s[i[0] - 1] != '\'' \
					&& s[i[0] -1] != '\"')) && word && i[1] > 0)
	{
		array[i[2]] = ft_substr(s, i[0] - i[1], i[1]);
		if (!array[i[2]])
			return (2);
		i[1] = 0;
		i[2]++;
	}
	return (0);
}

char	**fill_words(char *s, char **array)
{
	int		i[3];
	int		word;

	ft_bzero(i, sizeof(int) * 3);
	word = 0;
	while (s && s[i[0]])
	{
		while (s[i[0]] == ' ')
			i[0]++;
		if (s[i[0]])
			word++;
		while (s[i[0]] && s[i[0]] != ' ')
		{
			if (handle_all(s, i, array) == 2)
				return (NULL);
		}
		if (handle_new_word(s, i, array, word) == 2)
			return (NULL);
	}
	array[i[2]] = NULL;
	return (array);
}
