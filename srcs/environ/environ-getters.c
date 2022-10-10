/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ-getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:13:27 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/08 16:40:04 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 *
 * return t_environ_el* if key == t_environ_el.key
 *
 * @param {t_list_el *} entry
 * @param {char *} key
 *
 * @return {t_environ_el *}
 */
t_environ_el	*get_environ_el(t_list_el *entry, char *key)
{
	t_environ_el	*tmp;

	if (key == NULL || entry == NULL)
		return (NULL);
	while (entry)
	{
		tmp = entry->content;
		if (tmp != NULL && !ft_strncmp(key, tmp->key, ft_strlen(tmp->key)))
			return (tmp);
		entry = entry->next;
	}
	return (NULL);
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
	return (ft_strdup(tmp->value));
}
