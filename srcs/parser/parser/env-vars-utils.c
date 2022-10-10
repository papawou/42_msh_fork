/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-vars-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:01:56 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/09 14:52:28 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <stdlib.h>

int	count_number_of_env_variable(const char *str)
{
	int		i;
	int		number;

	i = 0;
	number = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
			number++;
		i++;
	}
	return (number);
}

/**
 *
 * Check if str contains a $ and so an env variable
 *
 * @param {char *} str
 *
 * @return {_Bool}
 */
_Bool	string_has_env_variable(const char *str)
{
	return (count_number_of_env_variable(str) > 0);
}

/**
 *
 * Extract the env variable from a cursor, set the start_env_variable
 * and set the cursor after the env variable
 *
 * @param {char *} cursor
 *
 * @return {char *} env_variable_key
 */
char	*extract_env_variable_key_from_str(
			t_env_variable *env_variable,
			char **cursor
		)
{
	int		i;
	int		length;
	char	*start_pos;
	char	*str;

	i = 0;
	length = 0;
	start_pos = NULL;
	str = *cursor;
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
	*cursor = start_pos + length;
	env_variable->start_of_variable = start_pos;
	return (ft_strndup(start_pos, length));
}

/**
 *
 * Calculate the length of the env variable token value
 * expanded with env variables
 *
 * @param {t_env_variable *} env_variable
 *
 * @return {int} length
 */
int	calculate_env_variable_expanded_length(t_env_variable *env_variable)
{
	return (
		env_variable->token_value_length
		- env_variable->key_length
		+ env_variable->value_length
	);
}
