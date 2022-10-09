/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:51:50 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/09 14:51:59 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

void	update_env_variable(t_env_variable *env_variable, char *token_value)
{
	char	*key_with_dollar;

	key_with_dollar = ft_strjoin("$", env_variable->key);
	env_variable->token_value = token_value;
	env_variable->token_value_length = ft_strlen(token_value);
	env_variable->start_of_variable = ft_strnstr(env_variable->token_value,
			key_with_dollar, env_variable->token_value_length);
	free(key_with_dollar);
}

void	expand_env_variable_string(
			t_env_variable *env_variable,
			char **value_addr
		)
{
	int				j;
	int				k;
	int				l;
	char			*expanded_value;
	char			*value;

	value = *value_addr;
	update_env_variable(env_variable, value);
	expanded_value = ft_calloc(calculate_env_variable_expanded_length(
				env_variable), sizeof(char));
	j = 0;
	k = 0;
	while (value[j] && &value[j] != env_variable->start_of_variable)
		expanded_value[k++] = value[j++];
	l = 0;
	while (env_variable->value[l])
		expanded_value[k++] = env_variable->value[l++];
	j += (env_variable->key_length + 1);
	while (value[j])
		expanded_value[k++] = value[j++];
	destroy_env_variable(env_variable);
	free(value);
	*value_addr = expanded_value;
}

/**
 *
 * Expend the env variable once, only string with env variable
 * need to be passed to this function
 *
 * @param {t_list_el *} env
 * @param {char *} value
 *
 * @return {char *}
 */
char	*expand_env_variables_string(t_list_el *env, char *value)
{
	int				i;
	t_env_variable	**env_variables;

	env_variables = init_env_variables(env, value);
	if (env_variables == NULL)
		return (value);
	i = 0;
	while (env_variables[i])
		expand_env_variable_string(env_variables[i++], &value);
	free(env_variables);
	return (value);
}

/**
 *
 * Expend the env variables (0 to n) in the token value
 *
 * @param {t_token *} token
 */
void	expend_env_variable(t_list_el *env, t_token *token)
{
	char	*value;

	if (!string_has_env_variable(token->value))
		return ;
	value = expand_env_variables_string(env, token->value);
	token->value = value;
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
		if (token->type == WORD_W_ENV_EXP)
			expend_env_variable(env, token);
		current_el = current_el->next;
	}
}
