/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tony <tony@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:40:43 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/26 16:35:51 by tony             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_exit(t_minishell *p, int code, int print)
{
	p->exit_status = code;
	free_everything(p, p->envp);
	if (print)
		ft_putstr_fd("exit\n", 2);
	exit(code);
}

static void	to_many_arguments(void)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}

static void	numeric_argument(char *str)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	builtin_exit(t_minishell *p, int forked)
{
	int	i;
	int	exit_code;

	i = 0;
	if (!p->input1[1])
		return (ft_exit(p, 0, 1));
	if (ft_strchr("+-", p->input1[1][0]))
		i++;
	while (p->input1[1][i])
	{
		if (!ft_isdigit(p->input1[1][i]))
			return (numeric_argument(p->input1[1]), ft_exit(p, 255, 0));
		i++;
	}
	if (p->input1[2])
		return (to_many_arguments(), ft_return(p, 1, forked));
	exit_code = ft_atoi(p->input1[1]);
	if (exit_code < 0)
		return (ft_exit(p, 256 - ((exit_code * -1) % 256), 1));
	return (ft_exit(p, exit_code % 256, 1));
}
