/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:14:44 by treeps            #+#    #+#             */
/*   Updated: 2023/05/17 11:20:08 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arrs(t_minishell *params)
{
	if (params->split_input)
		free_arr(params->split_input);
	if (params->cmd)
		free(params->cmd);
	if (params->paths)
		free_arr(params->paths);
	if (params->input1)
		free_arr(params->input1);
	if (params->usr_input)
		free(params->usr_input);
	params->split_input = NULL;
	params->usr_input = NULL;
	params->cmd = NULL;
	params->input1 = NULL;
	params->paths = NULL;
}

void	free_everything(t_minishell *p, t_env **env)
{
	free_arrs(p);
	if (p->heredoc)
		free_arr(p->heredoc);
	p->heredoc = NULL;
	if (env)
		free_env(env);
	env = NULL;
	if (p->pipefd)
		free(p->pipefd);
	p->pipefd = NULL;
	if (p->hd_pipe)
		free(p->hd_pipe);
	p->hd_pipe = NULL;
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
	return ;
}

void	free_strings(char **result, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(result[i]);
		i++;
	}
	free(result);
}
