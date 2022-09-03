/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:28:52 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/03 17:02:43 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*set_tokens_for_command(t_list_el **tokens)
{
	t_command	*command;
	t_list_el	*current_el;
	t_list_el	*last_el;
	t_token		*token;

	command = init_command();
	command->tokens = *tokens;
	current_el = *tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == PIPE)
		{
			last_el->next = NULL;
			*tokens = current_el->next;
			break ;
		}
		last_el = current_el;
		current_el = current_el->next;
	}
	return (command);
}

t_execution_plan	*parse_tokens(t_list_el *tokens)
{
	int					i;
	int					number_of_commands;
	t_execution_plan	*execution_plan;

	number_of_commands = count_number_of_commands(tokens);
	execution_plan = init_execution_plan(number_of_commands);
	i = 0;
	while (i < number_of_commands)
	{
		execution_plan->commands[i] = set_tokens_for_command(&tokens);
		if (!verify_tokens(execution_plan->commands[i]->tokens))
		{
			destroy_execution_plan(execution_plan);
			return (NULL);
		}
		set_io_from_tokens(execution_plan->commands[i]);
		set_argv_from_tokens(execution_plan->commands[i]);
		execution_plan->commands[i]->bin
			= ft_strdup(execution_plan->commands[i]->argv[0]);
		i++;
	}
	return (execution_plan);
}
