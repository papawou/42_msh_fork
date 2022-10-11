/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-vars-builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:41:43 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/09 14:49:54 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Init the t_env_variable from token value
 *
 * @param {char *} token_value
 *
 * @return {t_env_variable *}
 */
static t_env_variable	*init_env_variable(
		t_list_el *env,
		char *token_value,
		char **cursor
	)
{
	t_env_variable	*env_variable;

	env_variable = malloc(sizeof(t_env_variable));
	if (env_variable == NULL)
		return (NULL);
	env_variable->token_value = token_value;
	env_variable->token_value_length = ft_strlen(token_value);
	env_variable->key = extract_env_variable_key_from_str(env_variable, cursor);
	env_variable->key_length = ft_strlen(env_variable->key);
	env_variable->value = get_env_value(env, env_variable->key);
	if (env_variable->value == NULL && env_variable->key && env)
		env_variable->value = create_empty_str();
	env_variable->value_length = ft_strlen(env_variable->value);
	return (env_variable);
}

t_env_variable	*destroy_env_variables(t_env_variable **env_variables)
{
	int		i;

	i = 0;
	while (env_variables[i])
		destroy_env_variable(env_variables[i++]);
	free(env_variables);
	return (NULL);
}

t_env_variable	**init_env_variables(t_list_el *env, char *token_value)
{
	int				i;
	int				number_env_variables;
	char			*cursor;
	t_env_variable	**env_variables;

	number_env_variables = count_number_of_env_variable(token_value);
	env_variables
		= malloc(sizeof(t_env_variable *) * (number_env_variables + 1));
	if (env_variables == NULL)
		return (NULL);
	i = 0;
	cursor = token_value;
	while (i < number_env_variables)
	{
		env_variables[i] = init_env_variable(env, token_value, &cursor);
		if (env_variables[i] == NULL)
		{
			destroy_env_variables(env_variables);
			return (NULL);
		}
		i++;
	}
	env_variables[i] = NULL;
	return (env_variables);
}

t_env_variable	*destroy_env_variable(t_env_variable *env_variable)
{
	if (env_variable == NULL)
		return (NULL);
	free(env_variable->key);
	free(env_variable->value);
	free(env_variable);
	return (NULL);
}
