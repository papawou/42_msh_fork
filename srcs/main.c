/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:36:29 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/30 17:29:50 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <malloc.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

char	*get_prompt_name(void)
{
	char	*path;
	char	*prompt_name;
	int		buf_size;

	buf_size = 1024;
	path = malloc(sizeof(char) * buf_size);
	getcwd(path, buf_size);
	prompt_name = ft_strjoin(path, "$ ");
	free(path);
	return (prompt_name);
}

char	*prompt(char *line_read)
{
	char	*prompt_name;

	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	prompt_name = get_prompt_name();
	line_read = readline(prompt_name);
	free(prompt_name);
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
			execute_plan(execution_plan);
			destroy_execution_plan(execution_plan);
		}
	}
	free(line_read);
}
