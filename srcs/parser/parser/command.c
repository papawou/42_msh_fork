/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:31:48 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/09 19:04:22 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_number_of_commands(t_list_el *tokens)
{
	int			number_of_commands;
	t_list_el	*current_el;
	t_token		*token;

	number_of_commands = 0;
	current_el = tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == PIPE)
			number_of_commands++;
		current_el = current_el->next;
	}
	return (number_of_commands + 1);
}
