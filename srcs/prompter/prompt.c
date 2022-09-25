/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:37:56 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/26 20:34:54 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

#include "libft.h"
#include "minishell.h"

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
	char	*user_and_path;

	path = get_current_dir();
	user = ft_strjoin(getenv("USER"), "@");
	user_and_path = ft_strjoin(user, path);
	free(user);
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
	printf("\n***************************\n");
	printf("Welcome %s\n", getenv("USER"));
	printf("This shell was made for educational purpose.\n");
	printf("Be careful with it.\n");
	printf("***************************\n\n");
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
	if (line_read && line_read[0] != '\0')
		add_history(line_read);
	return (line_read);
}
