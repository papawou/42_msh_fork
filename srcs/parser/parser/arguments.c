/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:20:48 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/03 16:58:57 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

#include "minishell.h"

#include <stdlib.h>

char	*create_base_str(void)
{
	char	*str;

	str = malloc(sizeof(char));
	str[0] = '\0';
	return (str);
}

void	skip_n_elements(t_list_el **elements, int n)
{
	int			i;
	t_list_el	*current_el;

	current_el = *elements;
	i = 0;
	while (i < n)
	{
		if (current_el->next != NULL)
			current_el = current_el->next;
		else
			return ;
		i++;
	}
	*elements = current_el;
}

int	count_argv_from_tokens(t_command *command)
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
			|| token->type == OUTPUT_APPEND_OPERATOR)
			break ;
		if (token->type == SPACE_DELIMITER)
			i++;
		current_el = current_el->next;
	}
	return (++i);
}

void	set_argv_from_tokens(t_command *command)
{
	int			i;
	t_list_el	*current_el;
	t_list_el	*last_el;
	t_token		*token;
	char		*str;

	i = 0;
	command->argv = malloc(sizeof(char *)
			* (count_argv_from_tokens(command) + 1));
	current_el = command->tokens;
	last_el = NULL;
	str = create_base_str();
	while (current_el)
	{
		token = (t_token *)current_el->content;
		if (token->type == INPUT_SIMPLE_OPERATOR)
		{
			if (last_el == NULL)
				skip_n_elements(&current_el, 3);
			else
				skip_n_elements(&current_el, 2);
			continue ;
		}
		if (token->type == OUTPUT_SIMPLE_OPERATOR
			|| token->type == OUTPUT_APPEND_OPERATOR)
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
		last_el = current_el;
		current_el = current_el->next;
	}
	if (str[0] != '\0')
		command->argv[i++] = str;
	command->argv[i] = NULL;
}
