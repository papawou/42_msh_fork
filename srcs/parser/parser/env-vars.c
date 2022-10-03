/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:41:43 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/02 12:09:58 by fvarrin          ###   ########.fr       */
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
t_env_variable	*get_env_variable(t_list_el *env, char *token_value)
{
	t_env_variable	*env_variable;

	env_variable = malloc(sizeof(t_env_variable));
	if (env_variable == NULL)
		return (NULL);
	env_variable->token_value = token_value;
	env_variable->token_value_length = ft_strlen(token_value);
	env_variable->key = extract_env_variable_key_from_str(token_value);
	env_variable->key_length = ft_strlen(env_variable->key);
	env_variable->value = get_env_value(env, env_variable->key);
	if (env_variable->value == NULL && env_variable->key && env)
		env_variable->value = ft_strdup("");
	env_variable->value_length = ft_strlen(env_variable->value);
	return (env_variable);
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

/**
 *
 * Expend the env variable in the token value, only token with env variable
 * need to be pass to this function
 *
 * @param {t_token *} token
 */
void	expend_env_variable(t_list_el *env, t_token *token)
{
	int				i;
	int				y;
	int				z;
	char			*expanded_value;
	t_env_variable	*env_variable;

	env_variable = get_env_variable(env, token->value);
	if (env_variable == NULL)
		return ;
	expanded_value = ft_calloc(
			calculate_env_variable_expanded_length(env_variable), sizeof(char));
	i = 0;
	y = 0;
	while (token->value[i] && token->value[i] != '$')
		expanded_value[y++] = token->value[i++];
	z = 0;
	while (env_variable->value[z])
		expanded_value[y++] = env_variable->value[z++];
	i += (env_variable->key_length + 1);
	while (token->value[i])
		expanded_value[y++] = token->value[i++];
	destroy_env_variable(env_variable);
	free(token->value);
	token->value = expanded_value;
}

/**
 *
 * Expand variable in all needed tokens
 *
 * @param {t_list_el *} tokens
 */
void	parse_env_variables(t_list_el *env, t_list_el *tokens)
{
	t_list_el	*current_el;
	t_token		*token;

	current_el = tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		while (token->type == WORD_W_ENV_EXP
			&& str_has_env_variable(token->value))
			expend_env_variable(env, token);
		current_el = current_el->next;
	}
}
