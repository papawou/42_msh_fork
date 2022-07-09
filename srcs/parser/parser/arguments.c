/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:20:48 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/09 19:46:54 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

char *create_base_str(void)
{
	char	*str;

	str = malloc(sizeof(char));
	str[0] = '\0';
	return (str);
}

int count_argv_from_tokens(t_command *command)
{
	int			i;
	t_list_el	*current_el;
	t_token		*token;

	i = 0;
	current_el = command->tokens;
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == INPUT_SIMPLE_OPERATOR)
		{
			current_el = current_el->next->next;
			continue ;
		}
		if (token->type == OUTPUT_SIMPLE_OPERATOR
			||  token->type == OUTPUT_APPEND_OPERATOR)
			break ;
		if (token->type == SPACE_DELIMITER)
			i++;
		current_el = current_el->next;
	}
	return (++i);
}

void set_argv_from_tokens(t_command *command)
{
	int			i;
	int			number_of_arguments;
	t_list_el	*current_el;
	t_token		*token;
	char		*str;

	i = 0;
	number_of_arguments = count_argv_from_tokens(command);
	command->argv = malloc(sizeof(char *) * (number_of_arguments + 1));
	current_el = command->tokens;
	str = create_base_str();
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == INPUT_SIMPLE_OPERATOR)
		{
			current_el = current_el->next->next;
			continue ;
		}
		if (token->type == OUTPUT_SIMPLE_OPERATOR
		||  token->type == OUTPUT_APPEND_OPERATOR)
		{
			command->argv[i++] = str;
			str = create_base_str();
			break ;
		}
		if (token->type == WORD_WITH_ENV_EXPANSION
			|| token->type == WORD_WITHOUT_ENV_EXPANSION)
			str = ft_strjoin(str, token->value);
		else if (token->type == SPACE_DELIMITER)
		{
			command->argv[i++] = str;
			str = create_base_str();
		}
		current_el = current_el->next;
	}
	if (str[0] != '\0')
		command->argv[i++] = str;
	command->argv[i] = NULL;
	command->bin = ft_strdup(command->argv[0]);
}