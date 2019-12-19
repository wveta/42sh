/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repl_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/19 23:11:14 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_repl_check_end(char *s, char *q, int j)
{
//	char	*tmp;

	if (*q == ' ' && (s[j] == '\'' || s[j] == '"'))
	{
		*q = s[j];
//		tmp = s + j;
//		ft_strcpy(tmp, s + j + 1);
		return (1); //-1);
	}
	else if (*q != ' ' && (s[j] == *q))
	{
		*q = ' ';
//		tmp = s + j;
//		ft_strcpy(tmp, s + j + 1);
		return (1); //-1);
	}
	else if (s[j] == '\\' && *q != '\'')
	{
//		tmp = s + j;
//		ft_strcpy(tmp, s + j + 1);
		return (1); //2);
	}
	return (0);
}

int		ft_repl_check(char *s, int len, char *q, int j)
{
//	char	*tmp;

	if (*q == '\'')
	{
		if (s[j] == '\'')
		{
			*q = ' ';
//			tmp = s + j;
//			ft_strcpy(tmp, s + j + 1);
			return (1); //-1);
		}
		return (1);
	}
	else if (s[j] == '\\' && j + 1 < len && (s[j + 1] == '\''
		|| s[j + 1] == '"' || s[j + 1] == '\\'))
	{
//		tmp = s + j;
//		ft_strcpy(tmp, s + j + 1);
		return (1);
	}
	else
		return (ft_repl_check_end(s, q, j));
}
