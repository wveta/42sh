/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:34:55 by wveta             #+#    #+#             */
/*   Updated: 2019/11/28 15:24:46 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_setqflag(int *qflag, int val, int *wcount)
{
	*qflag = val;
	*wcount = *wcount + 1;
}

static int	ft_split_pipes_words(char *str)
{
	int		i;
	int		wcount;
	int		qflag;
	int		br_count;
	int		br_flag;
	int		flsub;

	i = 0;
	br_count = 0;
	br_flag = 0;
	wcount = 0;
	qflag = 0;
	flsub = 0;
	while (str && str[i])
	{

		if (qflag == 0 && (br_flag == 0 || br_flag == 1) &&
		str[i] == '(' && (i == 0 || ft_strchr(" ;|&$", str[i - 1])))
		{
			br_flag = 1;
			br_count++;
			if (br_count == 1 && str[i - 1] == '$' &&
			(i - 1 == 0 || str[i - 2] != '\\'))
				flsub = 1;
		}
		else if (qflag == 0 && br_flag == 1 && str[i] == '(')
			br_count++;
		else if (qflag == 0 && (br_flag == 0 || br_flag == 2) &&
		str[i] == '{' && (i == 0 || ft_strchr(" ;|&", str[i - 1])))
		{
			br_flag = 2;
			br_count++;
		}
		else if (qflag == 0 && br_flag == 2 && str[i] == '{')
			br_count++;
		if (qflag == 0 && ((br_flag == 1 && str[i] == ')') ||
		(br_flag == 2 && str[i] == '}')))
		{
			br_count--;
			if (br_count == 0)
			{
				br_flag = 0;
				if ((str[i] == ')') && (flsub == 1))
					flsub = 0;
				else
					wcount++;
				i++;
				continue;
			}
		}

		if (qflag == 0 && br_flag == 0 && str[i] == '|' &&
		(i == 0 || str[i - 1] != '\\'))
			wcount++;
		else if (qflag == 0 && br_flag == 0 && ft_isspace(str[i]) == 0 &&
		(i == 0 || ft_isspace(str[i - 1]) == 1
		|| (str[i - 1] == '|' && qflag == 0)))
			wcount++;
		if ((qflag == 1 && str[i] == '"' && str[i - 1] != '\\') ||
		(qflag == 2 && str[i] == '\'' && str[i - 1] != '\\'))
			qflag = 0;
		else if (qflag == 0 && str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
			qflag = 1;
		else if (qflag == 0 && str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
			qflag = 2;
		i++;
	}
	return (wcount);
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

	fl = ft_pipe_split_ini();
	flsub = 0;
	while (++fl->i < (int)ft_strlen(str) && (str[fl->i]))
	{

		if (fl->qflag == 0 && (fl->br_flag == 0 || fl->br_flag == 1) && str
		[fl->i] == '(' && (fl->i == 0 || ft_strchr(" ;|&$", str[fl-> i - 1])))
		{
			fl->br_flag = 1;
			fl->br_count++;
			if (fl->br_count == 1 && str[fl->i - 1] == '$' &&
			(fl->i - 1 == 0 || str[fl->i - 2] != '\\'))
				flsub = 1;
			else if (fl->br_count == 1 && flsub == 0)
				fl->start = fl->i;
		}
		else if (fl->qflag == 0 && fl->br_flag == 1 && str[fl->i] == '(')
			fl->br_count++;
		if (fl->qflag == 0 && (fl->br_flag == 0 || fl->br_flag == 2) && str
		[fl->i] == '{' && (fl->i == 0 || ft_strchr(" ;|&", str[fl->i - 1])))
		{
			fl->br_flag = 2;
			fl->br_count++;
			if (fl->br_count == 1)
				fl->start = fl->i;
		}
		else if (fl->qflag == 0 && fl->br_flag == 2 && str[fl->i] == '{')
			fl->br_count++;
		if (fl->qflag == 0 && ((fl->br_flag == 1 && str[fl->i] == ')') ||
		(fl->br_flag == 2 && str[fl->i] == '}')))
		{
			fl->br_count--;
			if (fl->br_count == 0)
			{
				fl->br_flag = 0;
				if ((str[fl->i] == ')') && (flsub = 1))
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
		(fl->i == 0 || str[fl->i - 1] != '\\'))
			ft_pipe_split_3(fl, ret, str);
		else if (fl->qflag == 0 && fl->br_flag == 0 && fl->flag == 1 &&
		ft_isspace(str[fl->i]) == 1 && fl->i > 0 &&
		ft_isspace(str[fl->i - 1]) == 0)
			ft_pipe_split_4(fl, ret, str);
		else
			ft_pipe_split_6(fl, str);
		if ((fl->qflag == 1 && str[fl->i] == '"' && str[fl->i - 1] != '\\') ||
			(fl->qflag == 2 && str[fl->i] == '\'' && str[fl->i - 1] != '\\'))
			fl->qflag = 0;
		else if (fl->qflag == 0 && str[fl->i] == '"' &&
		(fl->i == 0 || str[fl->i - 1] != '\\'))
			fl->qflag = 1;
		else if (fl->qflag == 0 && str[fl->i] == '\'' &&
		(fl->i == 0 || str[fl->i - 1] != '\\'))
			fl->qflag = 2;
	}
	if (fl->br_flag != 0)
	{
		ft_print_msg(" : parse error : ", (char *)str + fl->start);
		free(fl);
		return (-1);
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

	if (!s)
		return (NULL);
	count = ft_split_pipes_words(s);
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
	ret	= ft_cnt_subs(ret);
	return (ret);
}
