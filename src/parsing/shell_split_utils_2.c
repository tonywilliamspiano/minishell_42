/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tony <tony@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:14:01 by awilliam          #+#    #+#             */
/*   Updated: 2023/05/26 16:38:18 by tony             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*append_var_helper(char *s, char *ret, char *tmp, int i)
{
	char	*tmp2;
	char	*to_free;

	tmp2 = malloc(i + 1);
	if (!tmp2)
		return (free(s), free(tmp), NULL);
	ft_strlcpy(tmp2, s, i + 1);
	to_free = tmp;
	tmp = ft_strjoin(tmp2, tmp);
	free(to_free);
	free(tmp2);
	if (!tmp)
		return (free(s), NULL);
	if (ret)
		tmp = ft_strjoinf(ret, tmp);
	return (tmp);
}

static char	*append_var(t_minishell *p, char *s, int i, char *ret)
{
	int		len;
	char	*tmp;
	char	*var;

	if (ft_isdigit(s[i + 1]))
		len = 2;
	else
		len = ft_strlenc(&s[i + 1], \
		next_one(&s[i + 1], "\'\" /=\n:$[]{};()%")) + 1;
	var = malloc(len);
	if (!var)
		return (free(s), malloc_error(p, 1, 0), NULL);
	ft_strlcpy(var, &s[i + 1], len);
	if (s[i + 1] == '?')
		tmp = ft_itoa(p->exit_status);
	else
	{
		tmp = ft_getenv(var, *p->envp);
		if (!tmp || len == 1)
			tmp = ft_strdup("");
		else
			tmp = ft_strdup(tmp);
	}
	free(var);
	return (append_var_helper(s, ret, tmp, i));
}

static char	*expand_helper(char *ret, char *to_free, char *s)
{
	char	*tmp;

	tmp = ret;
	ret = ft_strjoin(ret, s);
	free(tmp);
	free(to_free);
	to_free = NULL;
	return (ret);
}

char	*expand_variables(t_minishell *p, char *s, char *orig_s, int i)
{
	char	*to_free;
	char	*ret;

	ret = NULL;
	if (s[0] == '$' && orig_s && is_apo(*orig_s))
		s[0] = 0;
	if (*s == 34 && orig_s)
		string_shift(s);
	to_free = s;
	while (s[++i])
	{
		if (s[i] == '$' && s[i + 1] && !ft_strchr("\'\" /=\n:$[]{};()%", s[i + 1]))
		{
			ret = append_var(p, s, i, ret);
			if (!ret)
				return (malloc_error(p, 1, 0), NULL);
			s++;
			if (ft_isdigit(s[i + 1]))
				s += i + 1;
			else
				s += i + ft_strlenc(&s[i], next_one(&s[i], "\'\" /=\n:$[]{};()%"));
			i = -1;
		}
	}
	return (expand_helper(ret, to_free, s));
}

char	next_one(char *s, char *set)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (ft_strchr(set, s[i]))
			return (s[i]);
		i++;
	}
	return (0);
}
