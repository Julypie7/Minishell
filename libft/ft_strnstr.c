/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <martalop@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:27:32 by martalop          #+#    #+#             */
/*   Updated: 2024/05/20 20:46:11 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
//#include <stddef.h>

/*size_t	ft_strlen(const char *s)
{
	size_t	indx;

	indx = 0;
	while (s[indx] != '\0')
		indx++;
	return (indx);
}
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hstk;
	char	*ndl;
	size_t	i;
	size_t	j;

	hstk = (char *) haystack;
	ndl = (char *) needle;
	i = 0;
	j = 0;
	if (ndl[j] == '\0')
		return (hstk);
	while (hstk[i] != '\0' && i < len)
	{
		j = 0;
		while ((hstk[i + j] == ndl[j]) && (i + j < len))
		{
			if (ndl[j + 1] == '\0')
				return (&hstk[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	*haystack;
	const char	*haystack_1;

	const char	*needle;
	const char	*needle_1;
	size_t	len;

	haystack = "\0";
	haystack_1 = "\0";
	needle = "ipsumm";
	needle_1 = "ipsumm";
	len = 6 * sizeof(char);
	printf("%s\n", ft_strnstr(haystack, needle, len));
	printf("%s\n", strnstr(haystack_1, needle_1, len));
	return (0);
}*/
