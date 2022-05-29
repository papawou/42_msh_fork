/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:36:29 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/29 16:50:50 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <malloc.h>
#include <readline/history.h>
#include <unistd.h>
#include "minishell.h"

char	*prompt(char *line_read)
{
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline(SHELL_PROMPT_NAME);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

int	main(void)
{
	char				*line_read;
	t_execution_plan	*execution_plan;

	line_read = NULL;
	while (42)
	{
		line_read = prompt(line_read);
		line_read = trim_space(line_read);
		if (line_read == NULL)
			break ;
		if (*line_read)
		{
			execution_plan = parse_line(line_read);
			destroy_execution_plan(execution_plan);
		}
	}
	free(line_read);
}
