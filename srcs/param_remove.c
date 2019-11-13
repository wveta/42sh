/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/11/11 16:02:55 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *param_remlarge_rev(char *var, char *pat)
{
	int		i;
	int		pos;

	pos = -1;
	i = ft_strlen(var) - 1;
	while (i > -1)
	{
		if (glob_check(&var[i], pat, 0, 0))
			pos = i;
		i--;
	}
	if (pos > -1)
		var[pos] = 0;
	return (var);
}

static char *param_remsmall_rev(char *var, char *pat)
{
	int		i;

	i = ft_strlen(var) - 1;
	while (i > -1)
	{
		if (glob_check(&var[i], pat, 0, 0))
		{
			var[i] = 0;
			break ;
		}
		i--;
	}
	return (var);
}

static char *param_remlarge(char *val, char *pat)
{
	char	save;
	int		i;
	int		pos;

	i = 0;
	pos = -1;
	while (val[i])
	{
		save = val[i + 1];
		val[i + 1] = 0;
		if (glob_check(val, pat, 0, 0))
			pos = i;
		val[i + 1] = save;
		i++;
	}
	if (pos > -1)
		ft_memmove(val, &val[pos + 1], ft_strlen(&val[pos]) + 1);
	return (val);
}

static char *param_remsmall(char *val, char *pat)
{
	char	save;
	int		i;

	i = 0;
	while (val[i])
	{
		save = val[i + 1];
		val[i + 1] = 0;
		if (glob_check(val, pat, 0, 0))
		{
			val[i + 1] = save;
			ft_memmove(val, &val[i + 1], ft_strlen(&val[i]) + 1);
			break ;
		}
		val[i + 1] = save;
		i++;
	}
	return (val);
}

char	*param_rem(char *val, char *flag, char *pat)
{
	if (!val || !*val || !flag || !*flag)
		return (NULL);
	if (!pat || !*pat)
		return (val);
	if (ft_strequ(flag, "#"))
		return (param_remsmall(val, pat));
	if (ft_strequ(flag, "##"))
		return (param_remlarge(val, pat));
	if (ft_strequ(flag, "%"))
		return (param_remsmall_rev(val, pat));
	if (ft_strequ(flag, "%%"))
		return (param_remlarge_rev(val, pat));
	return (NULL);
}
