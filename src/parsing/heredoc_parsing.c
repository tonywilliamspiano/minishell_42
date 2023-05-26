/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:39:58 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/17 11:43:43 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_min(int x, int y)
{
	if (x <= y)
		return (x);
	else
		return (y);
}

static void	delim_helper_2(t_minishell *p, char *tmp, char *delim, int hd_i)
{
	char	*to_free;

	while (ft_strncmp(tmp, delim, ft_strlen(delim)))
	{
		p->heredoc[hd_i] = ft_strjoinf(p->heredoc[hd_i], tmp);
		if (!p->heredoc[hd_i])
			malloc_error(p, 0, 0);
		tmp = readline("> ");
		if (!tmp)
		{
			ft_putstr_fd("\033[A> ", 2);
			break ;
		}
		to_free = tmp;
		tmp = ft_strjoin(tmp, "\n");
		if (!tmp)
			malloc_error(p, 0, 0);
		free(to_free);
	}
	if (tmp)
		free(tmp);
}

static void	delim_helper(t_minishell *p, char *loc, int len, int hd_i)
{
	char	*delim;
	char	*to_free;
	char	*tmp;

	delim = malloc(len + 2);
	if (!delim)
		malloc_error(p, 0, 0);
	ft_strlcpy(delim, loc, len + 1);
	delim[len] = '\n';
	delim[len + 1] = 0;
	tmp = readline("> ");
	if (!tmp)
		return (free(delim));
	to_free = tmp;
	tmp = ft_strjoin(tmp, "\n");
	if (!tmp)
		malloc_error(p, 0, 0);
	free(to_free);
	delim_helper_2(p, tmp, delim, hd_i);
	free(delim);
	delim = NULL;
}

int	count_delims(char **arr)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], "<<", 3))
			count++;
		i++;
	}
	return (count);
}

void	delimit_this(t_minishell *p)
{
	char	**arr;
	int		i;
	int		hd_i;

	p->heredoc = ft_calloc((count_delims(p->split_input) + 1), sizeof(char *));
	if (!p->heredoc)
		return (malloc_error(p, 1, 0));
	hd_i = 0;
	arr = p->split_input;
	i = 0;
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], "<<", 3))
		{
			delim_helper(p, arr[i + 1], ft_strlen(arr[i + 1]), hd_i);
			if (p->heredoc[hd_i])
				p->heredoc[hd_i] = expand_variables(p, p->heredoc[hd_i], 0, -1);
			else
				p->heredoc[hd_i] = ft_strdup("");
			hd_i++;
		}
		i++;
	}
	p->heredoc[hd_i] = NULL;
}
