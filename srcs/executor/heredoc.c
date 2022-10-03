/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:21:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/03 19:26:45 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <readline/readline.h>

/**
 * Prompt the user for the next command.
 * It frees line_read if already set and allocate memory for the next line.
 *
 * @param {char *} line_read
 *
 * @return {char *} line_read
 */
char	*prompt_heredoc(char *line_read)
{
	char	*prompt_name;

	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	prompt_name = ft_strdup("> ");
	line_read = readline(prompt_name);
	free(prompt_name);
	return (line_read);
}

_Bool	open_tmp_file(int *tmp_file_fd)
{
	*tmp_file_fd = open_file(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC);
	if (*tmp_file_fd < 1)
	{
		print_custom_error("heredoc", "Could not create tmp file");
		return (false);
	}
	ft_printf_fd(*tmp_file_fd, "");
	return (true);
}

void	execute_heredoc(char *heredoc, int tmp_file_fd)
{
	char		*line_read;

	line_read = NULL;
	while (42)
	{
		line_read = prompt_heredoc(line_read);
		if (!line_read)
		{
			ft_printf_fd(2, "%s (wanted `%s')\n",
				HEREDOC_EOF_WARNING, heredoc);
			break ;
		}
		if (ft_strcmp(line_read, (char *)heredoc) == 0)
			break ;
		ft_printf_fd(tmp_file_fd, "%s\n", line_read);
	}
	free(line_read);
}

/**
 *
 * Prompt for heredoc and write it to a tmp file
 *
 * @param {t_command *} command
 */
void	execute_heredocs(t_command *command)
{
	int			tmp_file_fd;
	t_list_el	*current_el;

	current_el = command->heredoc;
	while (current_el)
	{
		open_tmp_file(&tmp_file_fd);
		execute_heredoc(current_el->content, tmp_file_fd);
		current_el = current_el->next;
	}
	close(tmp_file_fd);
}
