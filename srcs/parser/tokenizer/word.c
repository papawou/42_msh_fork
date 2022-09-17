/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:15:21 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/17 14:24:53 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

/**
 *
 * Check that there is no unclosed quote in str
 *
 * @param {char *} str
 *
 * @return {_Bool}
 */
_Bool	check_quote_closed(char *str)
{
	int		i;
	int		number_of_double;
	int		number_of_single;

	number_of_double = 0;
	number_of_single = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			number_of_double++;
		else if (str[i] == '\'')
			number_of_single++;
		i++;
	}
	if (number_of_double % 2 != 0)
		return (false);
	if (number_of_single % 2 != 0)
		return (false);
	return (true);
}

/**
 *
 * @param {char **} str
 * @param {t_token *} token
 * @param {char} quote
 */
void	_set_quoted_word(char **str, t_token *token, char quote)
{
	int		i;

	i = 1;
	token->type = WORD_W_ENV_EXP;
	while ((*str)[i] != quote)
		i++;
	token->value = ft_strndup(*str + 1, i - 1);
	*str = &((*str)[i + 1]);
}

/**
 *
 * @param {char **} str
 * @param {t_token *} token
 */
void	set_double_quote_word(char **str, t_token *token)
{
	_set_quoted_word(str, token, '"');
}

/**
 *
 * @param {char **} str
 * @param {t_token *} token
 */
void	set_single_quote_word(char **str, t_token *token)
{
	_set_quoted_word(str, token, '\'');
}

/**
 *
 * Set given token to simple word
 *
 * @param {char **} str
 * @param {t_token *} token
 */
void	set_simple_word(char **str, t_token *token)
{
	int		i;

	i = 0;
	token->type = WORD_W_ENV_EXP;
	while ((*str)[i] && (*str)[i] != ' ' && !is_operator_symbol((*str)[i]))
		i++;
	token->value = ft_strndup(*str, i);
	*str = &((*str)[i]);
}
