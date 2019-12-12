/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:34:55 by wveta             #+#    #+#             */
/*   Updated: 2019/12/12 13:19:06 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_setqflag(int *qflag, int val, int *wcount)
{
	*qflag = val;
	*wcount = *wcount + 1;
}

int			ft_get_word(char **ret, int count, int size, char const *s)
{
	if (*(s + size) == '\0')
		size = size + 1;
	ret[count] = (char *)malloc(sizeof(char) * (size + 1));
	if (ret[count] == NULL)
		return (-1);
	ret[count][size + 0] = '\0';
	ret[count] = ft_strncpy(ret[count], s, (size_t)(size));
	return (0);
}

static int	ft_all_pipe_words(char **ret, char const *str)
{
	t_pipeflag	*fl;
	int			flsub;
	int			b_sl;

	fl = ft_pipe_split_ini();
	flsub = 0;
	b_sl = 0;
	while (++fl->i < (int)ft_strlen(str) && (str[fl->i]))
	{
		if (fl->qflag != 2 && str[fl->i] == '\\' && ((b_sl = b_sl + 1)))
			b_sl = b_sl % 2;
		if (fl->qflag == 0 && (fl->br_flag == 0 || fl->br_flag == 1) &&
		str[fl->i] == '(' && b_sl == 0 &&
		(fl->i == 0 || ft_strchr(" ;|&$", str[fl->i - 1])))
		{
			fl->br_flag = 1;
			fl->br_count++;
			if (fl->br_count == 1 && fl->i > 0 && str[fl->i - 1] == '$' &&
			(fl->i - 1 == 0 || b_sl == 0))
				flsub = 1;
			else if (fl->br_count == 1 && flsub == 0)
				fl->start = fl->i;
		}
		else if (fl->qflag == 0 && (fl->br_flag == 0 || fl->br_flag == 2) &&
		str[fl->i] == '{' && b_sl == 0)
		{
			fl->br_flag = 2;
			fl->br_count++;
			if (fl->br_count == 1 && fl->i > 0 && str[fl->i - 1] == '$' &&
			(fl->i - 1 == 0 || b_sl == 0))
				flsub = 1;
			else if (fl->br_count == 1 && flsub == 0)
				fl->start = fl->i;
		}
		else if (fl->qflag == 0 && fl->br_flag == 1 && str[fl->i] == '('
		&& b_sl == 0)
			fl->br_count++;
		else if (fl->qflag == 0 && (fl->br_flag == 0 || fl->br_flag == 2) && str
		[fl->i] == '{' && b_sl == 0 &&
		(fl->i == 0 || ft_strchr(" ;|&", str[fl->i - 1])))
		{
			fl->br_flag = 2;
			fl->br_count++;
			if (fl->br_count == 1)
				fl->start = fl->i;
		}
		else if (fl->qflag == 0 && fl->br_flag == 2 && str[fl->i] == '{'
		&& b_sl == 0)
			fl->br_count++;
		if (fl->qflag == 0 && ((fl->br_flag == 1 && str[fl->i] == ')') ||
		(fl->br_flag == 2 && str[fl->i] == '}'))
		&& b_sl == 0)
		{
			fl->br_count--;
			if (fl->br_count == 0)
			{
				fl->br_flag = 0;
				if (flsub == 1)
					flsub = 0;
				else
				{
					fl->i++;
					ft_pipe_split_4(fl, ret, str);
					fl->i--;
				}
				continue;
			}
		}
		if (fl->qflag == 0 && fl->br_flag == 0 && str[fl->i] == '|' &&
		(fl->i == 0 || b_sl == 0))
			ft_pipe_split_3(fl, ret, str);
		else if (fl->qflag == 0 && fl->br_flag == 0 && fl->flag == 1 &&
		ft_isspace(str[fl->i]) == 1 && fl->i > 0 &&
		ft_isspace(str[fl->i - 1]) == 0)
			ft_pipe_split_4(fl, ret, str);
		else
			ft_pipe_split_6(fl, str);
		if ((fl->qflag == 1 && str[fl->i] == '"' && b_sl == 0) ||
			(fl->qflag == 2 && str[fl->i] == '\'' && b_sl == 0))
			fl->qflag = 0;
		else if (fl->qflag == 0 && str[fl->i] == '"' &&
		(fl->i == 0 || b_sl == 0))
			fl->qflag = 1;
		else if (fl->qflag == 0 && str[fl->i] == '\'' &&
		(fl->i == 0 || b_sl == 0))
			fl->qflag = 2;
		else if (fl->qflag == 0 && str[fl->i] != '\\' && b_sl == 1)
			b_sl = 0;
	}
	if (fl->flag == 1)
		ft_get_word(ret, fl->count, fl->i - fl->start, str + fl->start);
	free(fl);
	return (0);
}

char		**ft_split_pipes(char *s)
{
	int		count;
	char	**ret;
	int		myjob;

	if (!s || (count = ft_split_pipes_words(s)) == 0)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (count + 1));
	if (ret == NULL)
		return (NULL);
	else
	{
		ret[count] = NULL;
		if (ft_all_pipe_words(ret, s) == -1 || ft_parse_pipe(ret))
		{
			ft_free_char_matr(ret);
			return (NULL);
		}
	}
	myjob = g_job;
	ret = ft_cnt_subs(ret);
	g_job = myjob;
	ret = ft_resize_matr(ret);
	ret = ft_press_matr(ret);
	return (ret);
}
