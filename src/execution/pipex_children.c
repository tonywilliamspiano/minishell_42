/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awilliam <awilliam@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:46:31 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/03 11:04:58 by awilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_helper(t_minishell *p, int in, int out)
{
	rl_clear_history();
	set_pipes(p, in, out);
	if (run_builtin(p, 1))
		return ;
	if (access(p->cmd, X_OK) == -1 || p->dircheck)
		cmd_error(p->input1[0], p);
	if (execve(p->cmd, p->input1, export_env(*p->envp)) < 0)
		error_handler("execve", p);
}

void	run_child_1(t_minishell *p, int in, int out)
{
	if (in)
		dup2(p->fd_in, STDIN_FILENO);
	if (out)
		dup2(p->fd_out, STDOUT_FILENO);
	run_helper(p, in, out);
}
