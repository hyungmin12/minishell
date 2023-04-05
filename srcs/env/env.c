/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:28:25 by minslee           #+#    #+#             */
/*   Updated: 2023/04/05 11:06:35 by hyyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char	*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = malloc(sizeof(char) * size_env(lst) + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
				env[i++] = lst->value[j++];
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

int	env_init(t_mini *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->value = ft_strdup(env_array[0]); //환경변수
	env->next = NULL;
	mini->env = env; //mini구조체 안에있는 env, secret_env, token start 중 env
	i = 1;
	while (env_array && env_array[0] && env_array[i]) //env array가 계속 존재?..
	{
		// printf("%s\n", env_array[0]);
		// printf("%s\n", env_array[i]);
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->value = ft_strdup(env_array[i]); //env 벨류를 구조체에 저장
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

int	secret_env_init(t_mini *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->secret_env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
