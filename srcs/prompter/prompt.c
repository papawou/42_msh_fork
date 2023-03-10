/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:37:56 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/10 18:58:23 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <stdbool.h>

/**
 * Return an allocated string holding the prompt name
 *
 * @return {char *} prompt_name
 */
static char	*get_prompt_name(void)
{
	char	*path;
	char	*prompt_name;
	char	*user;
	char	*user_and_at;
	char	*user_and_path;

	path = get_current_dir();
	user = getenv("USER");
	if (user)
		user_and_at = ft_strjoin(user, "@");
	else
		user_and_at = ft_strdup("user@");
	user_and_path = ft_strjoin(user_and_at, path);
	free(user_and_at);
	free(path);
	prompt_name = ft_strjoin(user_and_path, "$ ");
	free(user_and_path);
	return (prompt_name);
}

/**
 * Print the terminal welcome message
 */
void	print_welcome_message(void)
{
	char	*user;

	user = getenv("USER");
	printf("\n***************************\n");
	if (user)
		printf("Welcome %s\n", getenv("USER"));
	else
		printf("Welcome\n");
	printf("This shell was made for educational purpose.\n");
	printf("Be careful with it.\n");
	printf("***************************\n\n");
}

_Bool	has_only_space(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i++]))
			return (false);
	}
	return (true);
}

/**
 * Prompt the user for the next command.
 * It frees line_read if already set and allocate memory for the next line.
 *
 * @param {char *} line_read
 *
 * @return {char *} line_read
 */
char	*prompt(char *line_read)
{
	char	*prompt_name;

	if (line_read != NULL)
	{
		free(line_read);
		line_read = NULL;
	}
	prompt_name = get_prompt_name();
	line_read = readline(prompt_name);
	free(prompt_name);
	if (line_read && !has_only_space(line_read))
		add_history(line_read);
	return (line_read);
}
