/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:17:47 by ineimatu          #+#    #+#             */
/*   Updated: 2024/08/23 13:32:53 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "minishell.h"
 * #include "struct.h"*/

#include "fake_struct.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void    env_to_list(t_info *info, char **env);

int ft_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub_s;

	i = (size_t) start;
	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(&s[i]))
	{
		len = ft_strlen(&s[i]);
	}
	sub_s = malloc(sizeof(char) * (len + 1));
	if (!sub_s)
		return (NULL);
	while ((i < (start + len)) && (start < ft_strlen(s)))
	{
		sub_s[j] = s[i];
		i++;
		j++;
	}
	sub_s[j] = '\0';
	return (sub_s);
}
void	init_struct(t_info *info, char **env)
{
	info->envp = NULL;
	env_to_list(info, env);
//	print_env(info->envp);
//	print_char_arr(arr);
}

int	envlst_size(t_envp *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->next != NULL)
		{
			lst = lst->next;
			i++;
		}
		else
		{
			i++;
			break ;
		}
	}
	return (i);
}

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (0);
	return (i);
}

void	add_node_to_env(t_envp **lst, t_envp *node)
{
	t_envp	*tmp;

	if(!(*lst))
	{
		(*lst) = node;
	}
	else
	{
		tmp = (*lst);
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = node;
	}
}

void	env_to_list(t_info *info, char **env)
{
	int		found_at;
	int			i;
	t_envp		*node;

	i = 0;
	while (env[i])
	{
		node = malloc(sizeof(t_envp) * 1);
		if (!node)
		{
			write(2, "malloc error at env copy creation\n", 34);
			exit(1);
		}
		// variable name
		found_at = find_equal(env[i]);
		node->key = ft_substr(env[i], 0, found_at + 1);
		if (!node->key)
		{
					exit (1);
		}
		// content of variable
		node->value = ft_substr(env[i], found_at + 1, ft_strlen(env[i]) - found_at);
		if (!node->value)
		{
			free(node->key);
			exit (1);
		}
		node->next = NULL;
		add_node_to_env(&info->envp, node);
		i++;
	}
}

void mini_pwd(t_envp *info)
{
	t_envp *tmp;

	tmp = info;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{	
			printf("%s\n", tmp->value);
			exit (1);
		}
		else
			tmp = tmp->next;
	}
}

int main(int argc, char **argv, char **env)
{	
	t_info	*info;

	init_struct(info, env);
	if (ft_strcmp(argv[0], "pwd") == 0)
	{
		if(argv[1])
			printf("No such file or directory\n");
		else
			mini_pwd(info->envp);
	}
	return (0);
}
