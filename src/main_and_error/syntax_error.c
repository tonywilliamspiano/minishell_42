/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tony <tony@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:48:50 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/26 16:44:45 by tony             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_error(t_minishell *p, char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	g_es = 258;
	free_everything(p, NULL);
}

int	special_no_quotes(char *s, int check_pipes)
{
	if (!*s)
		return (0);
	if (check_pipes && !ft_strncmp(s, "|", 2))
		return (1);
	if (!ft_strncmp(s, ">", 2))
		return (1);
	if (!ft_strncmp(s, "<", 2))
		return (1);
	if (!ft_strncmp(s, ">>", 3))
		return (1);
	if (!ft_strncmp(s, "<<", 3))
		return (1);
	return (0);
}

int	check_syntax(t_minishell *p, char **arr)
{
	int	i;

	if (!ft_strncmp(arr[0], "|", 2))
		return (parse_error(p, arr[0]), 1);
	i = 0;
	while (arr[i])
	{
		if (arr[i + 1] && special_no_quotes(arr[i], 0) \
		&& special_no_quotes(arr[i + 1], 1))
			return ((parse_error(p, arr[i + 1])), 1);
		if (arr[i + 1] && !ft_strncmp(arr[i], "|", 2) \
		&& !ft_strncmp(arr[i + 1], "|", 2))
			return ((parse_error(p, arr[i + 1])), 1);
		i++;
	}
	return (0);
}

int	prs_err(t_minishell *p, int i)
{
	if (!p->split_input[i + 1] || !*(p->split_input[i + 1]))
	{
		if (p->split_input[i][0] == '|')
		{
			parse_error(p, "|");
			return (1);
		}
		else
		{
			parse_error(p, "newline");
			return (1);
		}
	}
	return (0);
}
