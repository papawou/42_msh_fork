/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:36:29 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/29 13:43:02 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <malloc.h>
#include <readline/history.h>
#include <signal.h>
#include "minishell.h"

char *prompt(char *line_read)
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

	line_read = NULL;
	while (42)
	{
		line_read = prompt(line_read);
		if (strcmp(line_read, "exit") == 0)
			break ;
		if (line_read && *line_read)
			printf("%s\n", line_read);
	}
	free(line_read);
}
