/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:14:54 by wveta             #+#    #+#             */
/*   Updated: 2019/12/02 23:23:55 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "calc/include/arithmetic.h"

char	*ft_calc_str(char *str, char *pref, char *suff, char *tmp)
{
	str[0] = '\0';
	str = ft_strfjoin(str, pref);
	str = ft_strfjoin(str, tmp);
	str = ft_strfjoin(str, suff);
	return (str);
}

char	**ft_tst_calc(char **str, int n, int start, int end)
{
	char	*tmp;
	char	*pref;
	char	*suff;

	if (start == -1 || end == -1)
		return (str);
	pref = NULL;
	suff = NULL;
	if (end - start > 1)
	{
		if (start > 2)
			pref = ft_strndup(str[n], start - 1);
		if (str[n][end + 1] != '\0')
			suff = ft_strdup(str[n] + end + 1);
		tmp = ft_strdup(str[n] + start + 2);
		tmp[end - start - 3] = '\0';
		if (ft_check_ekran(pref, ft_strlen(pref)) < 2 && ((tmp = ft_calc(tmp))))
			str[n] = ft_calc_str(str[n], pref, suff, tmp);
		free(tmp);
		free(pref);
		free(suff);
	}
	return (str);
}

char	**ft_all_calc_tst(char **str)
{
	int		i;
	int		qflag;
	int		br_count;
	int		br_flag;
	int		start;
	int		end;
	int		b_sl;
	int		n;

	n = -1;
	g_calc = 0;
	while (str && str[++n])
	{
		i = -1;
		start = -1;
		end = -1;
		br_count = 0;
		br_flag = 0;
		qflag = 0;
		b_sl = 0;
		while (str[n][++i])
		{
			if (qflag != 2 && str[n][i] == '\\' && ((b_sl = b_sl + 1)))
				b_sl = b_sl % 2;
			if (qflag == 0)
				ft_cacl_test_b(&br_flag, &br_count, i, str[n]);
			if (qflag == 0 && ((br_flag == 1 && str[n][i] == ')') ||
			(br_flag == 2 && str[n][i] == '}')))
			{
				br_count--;
				if (br_count == 0)
				{
					br_flag = 0;
					if (start != -1 && str[n][start + 1] == '(' && ((end = i))
					&& ft_check_ekran(str[n], start - 1) < 2)
					{
						str = ft_tst_calc(str, n, start, end);
						if (g_calc != 0)
							return (str);
						i = -1;
						continue;
					}
				}
			}
			ft_calc_test_q(&qflag, str[n], i, &b_sl);
			if (qflag == 0 && br_flag == 0 && (i == 0 || b_sl == 0)
			&& str[n][i] == '$' && str[n][i + 1] && str[n][i + 1] == '(')
				start = i + 1;
			if (qflag == 0 && str[n][i] != '\\' && b_sl == 1)
				b_sl = 0;
		}
	}
	return (str);
}

char	*ft_calc(char *str)
{
	char		*ans;

	ans = calculator(str);
	if (ans)
	{
		ft_strdel(&str);
		str = ans;
	}
	else
	{
		g_calc = 1;
		ft_set_shell("?", "1");
	}
	return (str);
}
