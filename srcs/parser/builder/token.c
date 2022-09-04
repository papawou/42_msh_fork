/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:09:53 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/04 15:02:37 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

/**
 * Allocate memory for a token
 *
 * @return {t_token *} token
 */
t_token	*init_token(void)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = NULL;
	return (token);
}

/**
 *
 * Free all token memory
 *
 * @param token
 *
 * @return  {t_token *}
 */
t_token	*destroy_token(t_token *token)
{
	if (token->value != NULL)
		free(token->value);
	free(token);
	return (NULL);
}
