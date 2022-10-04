/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:52:45 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/02 11:45:43 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void	set_exactly_one_space_padding(char **line)
{
	char	*str;
	char	*tmp;
	int		i;
	int		y;

	str = *line;
	tmp = trim_space(str);
	str = malloc((ft_strlen(tmp) + 3) * sizeof(char));
	i = 0;
	y = 0;
	str[y++] = ' ';
	while (tmp[i])
		str[y++] = tmp[i++];
	str[y++] = ' ';
	str[y] = '\0';
	free(tmp);
	*line = str;
}

/**
 *
 * @param {char *} line
 *
 * @return {t_execution_plan *}
 */
t_execution_plan	*parse_line(t_list_el *env, char *line)
{
	t_execution_plan	*execution_plan;
	t_list_el			*tokens;

	if (check_quote_closed(line) == false)
	{
		print_custom_error(NULL, NULL, "Syntax error, unclosed quote");
		free(line);
		return (NULL);
	}
	set_exactly_one_space_padding(&line);
	tokens = tokenize_line(line);
	free(line);
	parse_env_variables(env, tokens);
	execution_plan = parse_all_tokens(tokens->next);
	destroy_token((void *)tokens);
	if (execution_plan != NULL && !check_if_need_to_fork(execution_plan))
		execution_plan->need_to_fork = false;
	return (execution_plan);
}
