/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expanse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:01:40 by martalop          #+#    #+#             */
/*   Updated: 2024/10/14 01:45:39 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "struct.h"
#include "expansion.h"

void	handle_another_sect_quotes(char *s, int *i)
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

int	another_count_sections(char *s)
{
	int	i;
	int	sect;

	i = 0;
	sect = 0;
	while (s && s[i])
	{
		sect++;
		if (s[i] == '\'' || s[i] == '\"')
			handle_another_sect_quotes(s, &i);
		else
		{
			while (s[i] && s[i] != '\'' && s[i] != '\"')
				i++;
		}
	}
	return (sect);
}

void	go_through_str(char *s, int *i, int *ctr, char q)
{
	int	j;
	int	c;

	j = *i;
	c = *ctr;
	if (q == '\'' || q == '\"')
	{
		while (s[j] && s[j] != q)
		{
			j++;
			c++;
		}
		if (s[j] == q)
			j++;
	}
	else
	{
		while (s[j] && s[j] != '\'' && s[j] != '\"')
		{
			j++;
			c++;
		}
	}
	*i = j;
	*ctr = c;
}

void	find_word_len(char *s, int *i, int *ctr, int *word_start)
{
	int	j;

	j = *i;
	if (s[j] == '\'')
	{
		j++;
		*word_start = j;
		go_through_str(s, &j, ctr, '\'');
	}
	else if (s[j] == '\"')
	{
		j++;
		*word_start = j;
		go_through_str(s, &j, ctr, '\"');
	}
	else
	{
		*word_start = j;
		go_through_str(s, &j, ctr, s[j]);
	}
	*i = j;
}

char	**another_special_split(char *s)
{
	int		i[2];
	int		sect;
	int		word_start;
	int		ctr;
	char	**arr;

	ft_bzero(i, sizeof(int) * 2);
	sect = another_count_sections(s);
	arr = malloc(sizeof(char *) * (sect + 1));
	if (!arr)
		return (NULL);
	while (s && s[i[0]])
	{
		word_start = 0;
		ctr = 0;
		find_word_len(s, &i[0], &ctr, &word_start);
		arr[i[1]] = ft_substr(s, word_start, ctr);
		if (!arr[i[1]])
			return (free_array(arr), NULL);
		i[1]++;
	}
	arr[i[1]] = NULL;
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
