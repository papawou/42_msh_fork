/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:45:18 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/03 12:45:18 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <printf.h>

#include "minishell.h"
#include "libft.h"

t_word	*create_word(char *str, int length, _Bool should_expend_variable)
{
	char 	*content;
	t_word	*word;

	word = (t_word *)malloc(sizeof(t_word));
	content = ft_strndup(str, length);
	word->content = trim_space(content);
	if (ft_strcmp(word->content, "<") == 0)
		word->word_type = INPUT_SIMPLE_OPERATOR;
	else if (ft_strcmp(word->content, "<<") == 0)
		word->word_type = INPUT_HEREDOC_OPERATOR;
	else if (ft_strcmp(word->content, ">") == 0)
		word->word_type = OUTPUT_SIMPLE_OPERATOR;
	else if (ft_strcmp(word->content, ">>") == 0)
		word->word_type = OUTPUT_APPEND_OPERATOR;
	else
	{
		if (should_expend_variable)
			word->word_type = WORLD_WITH_ENV_EXPENSION;
		else
			word->word_type = WORLD_WITHOUT_ENV_EXPENSION;
	}
	return (word);
}

void	delete_word(void *word)
{
	free(((t_word *)word)->content);
	free(word);
}

t_list_el	*split_into_words(t_list_el *words, char *command_as_str)
{
	int			i;
	int			start;
	t_word		*word;

	i = 0;
	start = 0;
	words = NULL;
	while (command_as_str[i])
	{
		while (command_as_str[i] && command_as_str[i] != ' ')
			i++;

		if ((command_as_str[i] == ' ' || !command_as_str[i]))
		{
			word = create_word(&command_as_str[start], i - start, true);
			ft_lstadd_back(&words, ft_lstnew(word));
			start = i;
		}
		i++;
		word = NULL;
		if (!command_as_str[start])
			break ;
	}
	return words;
}