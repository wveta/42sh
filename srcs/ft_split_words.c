/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:34:55 by wveta             #+#    #+#             */
/*   Updated: 2019/12/12 14:30:49 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_ini_quoteflag_spl(t_quoteflag *f)
{
	f->i = 0;
	f->br_count = 0;
	f->br_flag = 0;
	f->qflag = 0;
	f->flsub = 0;
	f->b_sl = 0;
}

void		ft_split_words_p2(t_quoteflag *f, char *str)
{
	if (f->qflag == 0 && f->br_flag == 1 && str[f->i] == '(' &&
	f->b_sl == 0)
		f->br_count++;
	else if (f->qflag == 0 && (f->br_flag == 0 || f->br_flag == 2) &&
	str[f->i] == '{' && f->b_sl == 0 &&
	(f->i == 0 || ft_strchr(" ;|&", str[f->i - 1])))
	{
		f->br_flag = 2;
		f->br_count++;
	}
	else if (f->qflag == 0 && f->br_flag == 2 && str[f->i] == '{' &&
	f->b_sl == 0)
		f->br_count++;
}

void		ft_split_words_p1(t_quoteflag *f, char *str)
{
	if (f->qflag != 2 && str[f->i] == '\\' && ((f->b_sl = f->b_sl + 1)))
		f->b_sl = f->b_sl % 2;
	if (f->qflag == 0 && (f->br_flag == 0 || f->br_flag == 1) &&
	str[f->i] == '(' && f->b_sl == 0 &&
	(f->i == 0 || ft_strchr(" ;|&$", str[f->i - 1])))
	{
		f->br_flag = 1;
		f->br_count++;
		if (f->br_count == 1 && f->i > 0 && str[f->i - 1] == '$' &&
		(f->i - 1 == 0 || f->b_sl == 0))
			f->flsub = 1;
	}
	else if (f->qflag == 0 && (f->br_flag == 0 || f->br_flag == 2) &&
	str[f->i] == '{' && f->b_sl == 0
	&& (f->i == 0 || ft_strchr(" ;|&$", str[f->i - 1])))
	{
		f->br_flag = 2;
		f->br_count++;
		if (f->br_count == 1 && f->i > 0 && str[f->i - 1] == '$' &&
		(f->i - 1 == 0 || f->b_sl == 0))
			f->flsub = 1;
	}
	else
		ft_split_words_p2(f, str);
}

int			ft_split_pipes_words(char *str)
{
	t_quoteflag	*f;
	int			wcount;

	f = ft_get_quoteflag();
	ft_ini_quoteflag_spl(f);
	wcount = 0;
	while (str && str[f->i])
	{
		ft_split_words_p1(f, str);
		if (f->qflag == 0 && ((f->br_flag == 1 && str[f->i] == ')') ||
		(f->br_flag == 2 && str[f->i] == '}')) && f->b_sl == 0)
		{
			f->br_count--;
			if (f->br_count == 0)
			{
				f->br_flag = 0;
				if (f->flsub == 1)
					f->flsub = 0;
				else
					wcount++;
				f->i++;
				continue;
			}
		}
		if (f->qflag == 0 && f->br_flag == 0 && str[f->i] == '|' &&
		(f->i == 0 || f->b_sl == 0))
			wcount++;
		else if (f->qflag == 0 && f->br_flag == 0 && ft_isspace(str[f->i]) == 0 &&
		(f->i == 0 || ft_isspace(str[f->i - 1]) == 1
		|| (str[f->i - 1] == '|' && f->qflag == 0)))
			wcount++;
		if ((f->qflag == 1 && str[f->i] == '"' && f->b_sl == 0) ||
		(f->qflag == 2 && str[f->i] == '\'' && f->b_sl == 0))
			f->qflag = 0;
		else if (f->qflag == 0 && str[f->i] == '"' && (f->i == 0 || f->b_sl == 0))
			f->qflag = 1;
		else if (f->qflag == 0 && str[f->i] == '\'' && (f->i == 0 || f->b_sl == 0))
			f->qflag = 2;
		else if (f->qflag == 0 && str[f->i] != '\\' && f->b_sl == 1)
			f->b_sl = 0;
		f->i++;
	}
	if (f->br_count > 0)
	{
		ft_print_msg(" : parse error : ", str);
		wcount = 0;
	}
	free(f);
	return (wcount);
}