/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:09:53 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/09 17:33:17 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

t_token	*init_token(void)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = NULL;
	return (token);
}

t_token	*destroy_token(t_token *token)
{
	if (token->value != NULL)
		free(token->value);
	free(token);
	return (NULL);
}
