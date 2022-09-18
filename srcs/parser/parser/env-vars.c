/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:41:43 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/18 14:19:13 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <stdlib.h>

_Bool	str_has_env_variable(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '$')
			return (true);
	}
	return (false);
}

char		*extract_env_variable_key_from_str(char *str)
{
	int		i;
	int		length;
	char	*start_pos;

	i = 0;
	length = 0;
	start_pos = NULL;
	while (str[i])
	{
		if (length > 0 && !ft_isalnum(str[i]))
			break ;
		else if (str[i] == '$')
			start_pos = &(str[i + 1]);
		else if (start_pos != NULL)
			length++;
		i++;
	}
	return ft_strndup(start_pos, length);
}

void	expend_env_variable(t_token *token)
{
	int		i;
	int		y;
	int 	z;
	int		value_length;
	char	*env_variable;
	int		env_variable_length;
	char	*env_variable_value;
	int		env_variable_value_length;
	char 	*expanded_value;

	env_variable = extract_env_variable_key_from_str(token->value);
	env_variable_length = ft_strlen(env_variable);
	value_length = ft_strlen(token->value);
	env_variable_value = get_env_value(env_variable);
	env_variable_value_length = ft_strlen(env_variable_value);
	expanded_value = ft_calloc(value_length - env_variable_length + env_variable_value_length, sizeof(char));
	i = 0;
	y = 0;
	while (token->value[i] && token->value[i] != '$')
		expanded_value[y++] = token->value[i++];
	z = 0;
	while (env_variable_value[z])
		expanded_value[y++] = env_variable_value[z++];
	i += (env_variable_length + 1);
	while (token->value[i] && token->value[i] != '$')
		expanded_value[y++] = token->value[i++];
	free(token->value);
	token->value = expanded_value;
}

void	parse_env_variables(t_list_el *tokens)
{
	t_list_el	*current_el;
	t_token		*token;

	current_el = tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == WORD_W_ENV_EXP && str_has_env_variable(token->value))
			expend_env_variable(token);
		current_el = current_el->next;
	}
}