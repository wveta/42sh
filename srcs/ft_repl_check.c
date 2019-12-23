/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repl_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/23 17:24:01 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_repl_check_end(char *s, char *q, int j)
{
	if (*q == ' ' && (s[j] == '\'' || s[j] == '"'))
	{
		*q = s[j];
		return (1);
	}
	else if (*q != ' ' && (s[j] == *q))
	{
		*q = ' ';
		return (1);
	}
	else if (s[j] == '\\' && *q != '\'')
	{
		return (1);
	}
	return (0);
}

int		ft_repl_check(char *s, int len, char *q, int j)
{
	if (*q == '\'')
	{
		if (s[j] == '\'')
		{
			*q = ' ';
			return (1);
		}
		return (1);
	}
	else if (s[j] == '\\' && j + 1 < len && (s[j + 1] == '\''
		|| s[j + 1] == '"' || s[j + 1] == '\\'))
	{
		return (1);
	}
	else
		return (ft_repl_check_end(s, q, j));
}
