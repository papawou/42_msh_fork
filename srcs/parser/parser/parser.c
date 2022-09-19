/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:28:52 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/25 15:57:51 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

/**
 *
 * Create a command and attach the correct tokens to it
 *
 * @param {t_list_el **} tokens
 *
 * @return {t_command *}
 */
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

/**
 *
 * Count the number of argv for a command
 * @TODO verify that always true with different syntax of input operator
 *
 * @param {t_command *} command
 *
 * @return {int} number_of_argv
 */
int	count_argv(t_command *command)
{
	int			i;
	t_list_el	*current_el;
	t_token		*token;

	i = 0;
	current_el = command->tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == I_SIMPLE_OP)
		{
			current_el = current_el->next->next;
			continue ;
		}
		if (token->type == O_SIMPLE_OP
			|| token->type == O_APPEND_OP)
			break ;
		if (token->type == SPACE_DELIMITER)
			i++;
		current_el = current_el->next;
	}
	return (++i);
}

/**
 *
 * Get the tokens and verify them, create the commands with io and argv and
 * attach them to a created execution_plan
 *
 * @param {t_list_el *} tokens
 *
 * @return {t_execution_plan *}
 */
t_execution_plan	*parse_tokens(t_list_el *tokens)
{
	int					i;
	int					number_of_commands;
	t_execution_plan	*execution_plan;
	char				*str;

	number_of_commands = count_number_of_commands(tokens);
	execution_plan = init_execution_plan(number_of_commands);
	i = -1;
	while (++i < number_of_commands)
	{
		execution_plan->commands[i] = set_tokens_for_command(&tokens);
		if (!verify_tokens(execution_plan->commands[i]->tokens))
		{
			destroy_execution_plan(execution_plan);
			return (NULL);
		}
		if (has_heredoc_token(execution_plan->commands[i]->tokens))
			handle_heredoc_input(execution_plan->commands[i]);
		set_io_from_tokens(execution_plan->commands[i]);
		execution_plan->commands[i]->argv = malloc(sizeof(char *)
				* (count_argv(execution_plan->commands[i]) + 1));
		str = create_base_str();
		set_argv_from_tokens(execution_plan->commands[i], &str);
		execution_plan->commands[i]->bin
			= ft_strdup(execution_plan->commands[i]->argv[0]);
		free(str);
	}
	return (execution_plan);
}
