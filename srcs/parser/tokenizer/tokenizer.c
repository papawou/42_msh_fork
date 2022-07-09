/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:23:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/09 17:33:40 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_token(char **str)
{
	t_token	*token;

	if (!has_more_tokens(*str))
		return (NULL);
	token = init_token();
	if (**str == ' ')
		set_space_delimiter(str, token);
	else
		set_simple_word(str, token);
	return (token);
}

t_list_el	*tokenize_line(char *line)
{
	char		**cursor;
	t_list_el	*list;
	t_token		*token;

	list = NULL;
	cursor = &line;
	token = get_next_token(cursor);
	if (token != NULL)
		ft_lstadd_back(&list, ft_lstnew(token));
	while (token != NULL)
	{
		token = get_next_token(cursor);
		if (token)
			ft_lstadd_back(&list, ft_lstnew(token));
	}
	return (list);
}
