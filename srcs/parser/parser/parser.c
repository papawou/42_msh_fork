/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:28:52 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/11 15:18:39 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

static void	handle_pipe_token(
		t_list_el **current_el,
		t_list_el *last_el,
		t_command *command,
		t_list_el **tokens
	)
{
	if (last_el != NULL)
		last_el->next = NULL;
	else
		command->tokens = NULL;
	*tokens = (*current_el)->next;
	ft_lstremove(current_el, *current_el, destroy_token);
}

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
	last_el = NULL;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == PIPE)
		{
			handle_pipe_token(&current_el, last_el, command, tokens);
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
		if (is_io_token(token))
		{
			current_el = current_el->next->next;
			continue ;
		}
		if (token->type == SPACE_DELIMITER)
			i++;
		current_el = current_el->next;
	}
	return (++i);
}

t_command	*parse_command_tokens(
	t_command *command,
	t_list_el **tokens,
	int idx)
{
	char		*str;

	if (!verify_first_is_not_pipe(*tokens))
		return (NULL);
	command = set_tokens_for_command(tokens);
	command->idx = idx;
	if (!verify_tokens(command->tokens))
	{
		destroy_command(command);
		return (NULL);
	}
	set_io_from_tokens(command);
	command->argv = malloc(sizeof(char *)
			* (count_argv(command) + 1));
	str = NULL;
	set_argv_from_tokens(command, &str);
	if (command->argv[0])
		command->bin
			= ft_strdup(command->argv[0]);
	free(str);
	return (command);
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
t_execution_plan	*parse_all_tokens(t_list_el *tokens)
{
	int					i;
	int					number_of_commands;
	t_execution_plan	*execution_plan;

	number_of_commands = count_number_of_commands(tokens);
	execution_plan = init_execution_plan(number_of_commands);
	i = 0;
	while (i < number_of_commands)
	{
		execution_plan->commands[i]
			= parse_command_tokens(execution_plan->commands[i], &tokens, i);
		if (execution_plan->commands[i] == NULL)
		{
			destroy_execution_plan(execution_plan);
			return (NULL);
		}
		i++;
	}
	return (execution_plan);
}
