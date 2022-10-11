/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:16:13 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/11 14:19:03 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "minishell.h"

/**
 *
 * Check if key_value param is a valid environment variable
 * formatted as #*[a-b,A-Z,0-9]=*.#
 *
 * @param {char *} key_value
 * @param {_Bool} accept_key_only
 *
 * @return {_Bool}
 */
_Bool	is_valid_key_value_env(char *key_value, _Bool is_key_only)
{
	int	i;

	i = 0;
	if (key_value == NULL)
		return (false);
	if (!ft_isalpha(key_value[0]))
		return (false);
	while (ft_isalnum(key_value[i]) || key_value[i] == '_')
		++i;
	if (key_value[i] == '\0')
		return (true);
	if (!is_key_only && key_value[i] == '=')
		return (true);
	return (false);
}

/**
 *
 * Get env variable value, return empty string if not found
 *
 * @return {char **} paths
 */
char	*get_env_value(t_list_el *env, char *key)
{
	t_environ_el	*tmp;
	t_list_el		*entry;

	entry = env;
	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(g_env_exit));
	if (entry == NULL || key == NULL)
		return (NULL);
	tmp = get_environ_el(entry, key);
	if (tmp == NULL)
		return (NULL);
	if (tmp->value == NULL)
		return (NULL);
	return (ft_strdup(tmp->value));
}

int	parse_key_value_environ_el(char *key_value, t_environ_el *el)
{
	char			*eq_ptr;

	if (key_value == NULL)
		return (1);
	if (key_value[0] == '\0')
		return (1);
	eq_ptr = ft_strchr(key_value, '=');
	if (!is_valid_key_value_env(key_value, false))
		return (1);
	el->key = ft_strndup(key_value, eq_ptr - key_value);
	if (eq_ptr)
		el->value = ft_strdup(eq_ptr + 1);
	else
		el->value = NULL;
	return (0);
}

/**
 *
 * parse char **environ from unistd.h to a linked list and return it
 * return value is NULL if environ vars is empty
 *
 * @return {t_list_el *}
 */
t_list_el	*parse_environ(void)
{
	int				i;
	t_list_el		*lst;

	i = 0;
	lst = NULL;
	while (environ[i])
		add_environ_el(&lst, environ[i++]);
	return (lst);
}
