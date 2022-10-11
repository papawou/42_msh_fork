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

//upsert
int	add_environ_el(t_list_el **entry, char *key_value)
{
	t_environ_el	*tmp;
	t_environ_el	parsed_el;

	if (key_value == NULL)
		return (1);
	if (parse_key_value_environ_el(key_value, &parsed_el))
		return (1);
	tmp = get_environ_el(*entry, parsed_el.key);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = parsed_el.value;
		return (0);
	}
	tmp = create_environ_el(parsed_el.key, parsed_el.value);
	if (tmp == NULL)
		return (1);
	ft_lstadd_front(entry, ft_lstnew(tmp));
	return (0);
}

//create
t_environ_el	*create_environ_el(char *key, char *value)
{
	t_environ_el	*dst;

	if (key == NULL)
		return (NULL);
	dst = (t_environ_el *) malloc(sizeof(t_environ_el));
	dst->key = key;
	dst->value = value;
	return (dst);
}

//get
t_environ_el	*get_environ_el(t_list_el *entry, char *key)
{
	t_environ_el	*tmp;

	if (entry == NULL || key == NULL)
		return (NULL);
	while (entry)
	{
		tmp = (t_environ_el *) entry->content;
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		entry = entry->next;
	}
	return (NULL);
}

/////////////////
/**
 *
 * @param {t_list_el **} entry
 * @param {char *} key
 */
void	remove_environ_el(t_list_el **entry, char *key)
{
	t_environ_el	*el;

	if (entry == NULL || key == NULL)
		return ;
	el = get_environ_el(*entry, key);
	ft_lstremove(entry, ft_lstfind_by_content(*entry, el), &destroy_environ_el);
}

/**
 *
 * use it for ft_lstdel(..., void (*del)(void *))
 *
 * @param {void *} el
 */
void	destroy_environ_el(void *el)
{
	if (el == NULL)
		return ;
	free(((t_environ_el *)el)->key);
	free(((t_environ_el *)el)->value);
	free(el);
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
