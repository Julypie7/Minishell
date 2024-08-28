/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:18:27 by ineimatu          #+#    #+#             */
/*   Updated: 2024/08/28 15:18:32 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "minishell.h"
 * #include "struct.h"*/

#include "fake_struct.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
/*
void	print_env(t_envp *lst)
{
	int	i;
	t_envp	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		printf("%s\n", tmp->key);
		tmp = tmp->next;
		i++;
	}
}
*/

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

void	init_struct(t_info *info, char **env)
{
	info->envp = NULL;
	env_to_list(info, env);
//	print_env(info->envp);
//	print_char_arr(arr);
}

/*
void	cambiar_env(t_envp *lst)
{
}

void	inti_paths(t_pwd *paths)
{
	
void	mini_cd(t_envp *lst)
{
	t_envp	*tmp;
	t_pwd	*path;
	int i;

	tmp = lst;
	i = 0;
	path = malloc(sizeof(t_pwd) * 1);
	if (!path)
	{
		write(2, "mallocerror\n", 12);
		exit (1);
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD=") == 0)
		{	
			path->pwd = malloc(sizeof(char) * (ft_strlen(tmp->value) + 1))
			if (!path->pwd)
				return (NULL);
			while (i < ft_strlen(tmp->value))
			{
				path->pwd[i] = tmp->value[i];
				i++;
			}
		}
		else if (ft_strncmp(tmp->key, "OLDPWD=") == 0)
		{
			path->oldpwd = malloc(sizeof(char) * (ft_strlen(tmp->value) + 1))
			if (!path->oldpwd)
				return (NULL);
			i = 0;
			while (i < ft_strlen(tmp->value))
			{
				path->oldpwd[i] = tmp->value[i];
				i++;
			}
		}
		else if

}*/

char	*ft_getenv(char *str, t_envp *lst)
{
	t_envp *tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return(tmp->value);
		else
			tmp = tmp->next;
	}
	return ("path doesn't exist");
}


char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

void change_pwd(t_envp *lst)
{
	t_envp *tmp;
	char *swop;

	tmp = lst;
	swop = getcwd(NULL, 0);
	while (lst)
	{
		if (ft_strcmp(lst->key, "PWD=") == 0)
		{
			free(lst->value);
			lst->value = malloc(sizeof(char) * (ft_strlen(swop) + 1));
			lst->value = ft_strcpy(lst->value, swop);
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	free(swop);
}

void	just_cd(t_envp *lst)
{
	t_envp	*tmp;
	tmp = lst;

	char *pwd;

	pwd = getcwd(NULL, 0);
	/*int i;
	i = chdir("/home/ineimatu");
	pwd = getcwd(NULL, 0);
	printf("%d\n %s\n", i, pwd);
*/
	if (chdir("/home/ineimatu") == -1)
	{	
		printf("cd: HOME not set\n");
		exit(1);
	}
	else
	{	
		change_pwd(lst);
		while (lst)
		{
			if (ft_strcmp(lst->key, "OLDPWD=") == 0)
			{
			//pwd = ft_strcpy(pwd, lst->value);
				free(lst->value);
				lst->value = malloc(sizeof(char) * (ft_strlen(pwd) + 1));
					if (!lst->value)
						return;
				lst->value = ft_strcpy(lst->value, pwd);
				printf("oldpwd %s\n", lst->value);
				printf("pwd %s\n", ft_getenv("PWD=", lst));
				break;
			}
			else
				lst = lst->next;
		}
	}
	printf("algo");
	lst = tmp;
	printf("before");
	change_pwd(lst);
	printf("after");
	printf("pwd %s\n", ft_getenv("PWD=", lst));
/*	while (lst)
	{
		if(ft_strcmp(lst->key, "OLDPWD=") == 0)
		{
		//	free(lst->value);
		//	lst->value = malloc(sizeof(char) * ft_strlen(pwd) + 1);
		//	lst->value = ft_strcpy(lst->value, pwd);
			printf("old pwd %s\n", lst->value);
		}
		else 
			lst = lst->next;
	}
	lst = tmp;*/
}

	


int main(int argc, char **argv, char **env)
{
	t_info	*info;

	init_struct(info, env);
	if (argc == 4)
	{	
		printf("Too many arguments\n");
		exit(1);
	}
	if (ft_strcmp(argv[1], "cd") == 0 && argc == 2)
			just_cd(info->envp);
	return (0);
}

