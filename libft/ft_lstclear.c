/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <martalop@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:33:06 by martalop          #+#    #+#             */
/*   Updated: 2024/09/08 16:57:29 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*static void	del(void *content)
{
	free(content);
}*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*tmp;

	if (!*lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current->next;
		del(current->content);
		free(current);
		current = tmp;
	}
	*lst = NULL;
}

/*int	main()
{
	t_list	*lst;
	t_list	node2;
	char	*s;
	char	*s2;

	s = (char *)malloc(sizeof(char) * 12);
	if (!s)
		return (0);
	ft_strlcpy(s, "to be freed", 12);
	s2 = (char *)malloc(sizeof(char) * 5);
	if (!s2)
		return (0);
	ft_strlcpy(s2, "hola", 5);
	node2.content = s2;
	node2.next = NULL;
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (free(s), 0);
	lst->content = s;
	lst->next = &node2;
//	printf("%s\n", lst->content);
//	printf("%s\n", lst->next->content);
	ft_lstclear(&lst, &del);
	printf("%s", lst->content);
	printf("%s", lst->next->content);
	return (0);
}*/
